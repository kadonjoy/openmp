/*
 **************************************************************************************
 *       Filename:  main_openmp.cc
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2018-03-30 13:49:36
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */


#include	<omp.h>
#include    <iostream>
#include    <vector>

using namespace std;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
    int
main ( int argc, char *argv[] )
{
    vector<int> a = {1,2,3,4,5,6,7,8};
    vector<int> b = {1,2,1,2,1,2,1,2};
    vector<int> c(8);
    int sum = 0;
    omp_set_num_threads(4);

// 第一种利用openmp parallel方式运行紧接着的for循环 
#pragma omp parallel for
    for(int i = 0; i < 8; i++)
    {
        c[i] = a[i] + b[i];
        printf("The 1st parallel c[%d]=%d tid: %d\n", i, c[i], omp_get_thread_num());
    }

    //这里是两个for循环之间的代码，将会由线程0即主线程执行  
    printf("I am Thread %d\n", omp_get_thread_num()); 

// 第二种利用openmp parallel方式运行紧接着的for循环 
#pragma omp parallel
{
#pragma omp for
    for(int i = 0; i < 8; i++)
    {
        c[i] = a[i] + b[i];
        printf("The 2nd parallel c[%d]=%d tid: %d\n", i, c[i], omp_get_thread_num());
    }

}

// 第一种处理openmp数据同步方式
#pragma omp parallel for
    for(int i = 0; i < 5000; i++) {
#pragma omp critical
        sum +=1;
    }

    cout << "sum = " << sum << endl;

// 第二种处理openmp数据同步方式
    sum = 0;
#pragma omp parallel
{
#pragma omp for reduction(+:sum)
    for(int i = 0; i < 5000; i++) {
        sum +=1;
    }
}
    cout << "sum2 = " << sum << endl;
    return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */



/********************************** END **********************************************/

