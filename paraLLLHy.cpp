#include "paraLLLHy.h"



LLLMatrix paraLLLHy(LLLMatrix B, int p, int fre, int b_size)
{

    int num_block = 2 * p;
    int m = B.cols();
    int block_size = m / num_block;
    int sub_size = b_size / num_block;

    std::random_device rd;  // Generate a random seed once
    std::mt19937 g(rd());   // Use Mersenne Twister as random engine

    std::vector<int> tags(num_block);
    for (int i = 0; i < num_block; ++i)
    {
        tags[i] = i;
    }

    std::vector<int> new_tags = tags;

    int temp = tags[num_block-1];

    // Shift the second element of each block to the next block
    for (int i = 1; i < num_block-2 ; i = i+2) {
        new_tags[i+2] = tags[i];
    }

    // Place the stored element from the last block into the first block
    new_tags[1] = temp;


    int iter = 0;
    Eigen::MatrixXd B_double = lllmatrix2matrixxd(B);
    Eigen::VectorXd norms = B_double.colwise().norm();
    double od_org = norms.array().log().sum();
    double od;

    //double od_org = B_double.colwise().norm().prod();


    while (true)
    {
        LLLMatrix B_org = B;
        //std::vector<Eigen::MatrixXd> B_cells(p);
        std::vector<double> cell_norms(p, 0);
#pragma omp parallel for
        for (int i = 0; i < p; ++i)
        {

            LLLMatrix block = B_org.block(0, tags[2 * i] * block_size, B_org.rows(), block_size);
            LLLMatrix block2 = B_org.block(0, tags[2 * i + 1] * block_size, B_org.rows(), block_size);
            LLLMatrix concatenated(B_org.rows(), block.cols() + block2.cols());
            concatenated << block, block2;
            LLLMatrix concatenated_trans = concatenated.transpose();


            auto blocks = lllmatrix2zzmat(concatenated_trans);
            //lll_reduction(blocks, fplll::LLL_DEF_DELTA, fplll::LLL_DEF_ETA, fplll::LM_PROVED, fplll::FT_MPFR, 0, fplll::LLL_DEFAULT);
            bkz_reduction(blocks, sub_size, fplll::BKZ_DEFAULT | fplll::BKZ_AUTO_ABORT, fplll::FT_DEFAULT, 0);
            //auto block_reduced = zzmat2lllmatrix(blocks).transpose();
            auto block_reduced = zzmat2lllmatrix(blocks);


            auto block_reduced_trans = block_reduced.transpose();
            Eigen::MatrixXd Bkk = lllmatrix2matrixxd(block_reduced_trans);
            Eigen::VectorXd norms2 = Bkk.colwise().norm();
            cell_norms[i] = norms2.array().log().sum();
            B.block(0, tags[2 * i] * block_size, B.rows(), block_size * 2) = block_reduced_trans;


        }

        iter++;
        if(iter == 1){
            tags = new_tags;
        }

        od = std::accumulate(cell_norms.begin(), cell_norms.end(), 0.0);

        if ((od / od_org) > 0.999999) {
            break;
        }
        od_org = od;


        if (iter == 40)
        {
            break;
        }

        if(iter % fre == 0){
            randomPermutation2(B,g);
        }

        //tags = CO2_ordering_new(tags_org, num_block);

    }


    LLLMatrix B_trans = B.transpose();
    auto fplllB = lllmatrix2zzmat(B_trans);
    //lll_reduction(fplllB, fplll::LLL_DEF_DELTA, fplll::LLL_DEF_ETA, fplll::LM_WRAPPER, fplll::FT_DEFAULT,  0, fplll::LLL_DEFAULT);
    bkz_reduction(fplllB, b_size, fplll::BKZ_DEFAULT | fplll::BKZ_AUTO_ABORT, fplll::FT_DEFAULT, 0);
    LLLMatrix final_B = zzmat2lllmatrix(fplllB).transpose();
    //std::cout <<"iter from para: "<<iter<<std::endl;
    return final_B;

}
