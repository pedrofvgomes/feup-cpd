#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <papi.h>

using namespace std;

#define SYSTEMTIME clock_t


void OnMult(int m_ar, int m_br)
{

    SYSTEMTIME Time1, Time2;

    char st[100];
    double temp;
    int i, j, k;

    double *pha, *phb, *phc;



    pha = (double *)malloc((m_ar * m_br) * sizeof(double));
    phb = (double *)malloc((m_ar * m_br) * sizeof(double));
    phc = (double *)malloc((m_ar * m_br) * sizeof(double));

    for(i=0; i<m_ar; i++)
        for(j=0; j<m_ar; j++)
            pha[i*m_ar + j] = (double)1.0;



    for(i=0; i<m_br; i++)
        for(j=0; j<m_br; j++)
            phb[i*m_br + j] = (double)(i+1);



    Time1 = clock();

    for(i=0; i<m_ar; i++)
    {	for( j=0; j<m_br; j++)
        {	temp = 0;
            for( k=0; k<m_ar; k++)
            {
                temp += pha[i*m_ar+k] * phb[k*m_br+j];
            }
            phc[i*m_ar+j]=temp;
        }
    }


    Time2 = clock();
    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
    cout << st;

    // display 10 elements of the result matrix tto verify correctness
    cout << "Result matrix: " << endl;
    for(i=0; i<1; i++)
    {	for(j=0; j<min(10,m_br); j++)
            cout << phc[j] << " ";
    }
    cout << endl;

    free(pha);
    free(phb);
    free(phc);


}

// add code here for line x line matriz multiplication
void OnMultLine(int m_ar, int m_br) {
    SYSTEMTIME Time1, Time2;

    char st[100];
    int i, j, k;

    double *pha, *phb, *phc;

    pha = (double *)malloc((m_ar * m_br) * sizeof(double));
    phb = (double *)malloc((m_ar * m_br) * sizeof(double));
    phc = (double *)malloc((m_ar * m_br) * sizeof(double));

    // initialize matrix a - identity
    for (i = 0; i < m_ar; i++)
        for (j = 0; j < m_br; j++)
            pha[i * m_ar + j] = (double)1.0;

    // initialize matrix b - each row is filled with its index + 1
    for (i = 0; i < m_ar; i++)
        for (j = 0; j < m_br; j++)
            phb[i * m_br + j] = (double)(i + 1); 

    Time1 = clock();

    for(i=0; i<m_ar; i++)
        for(j=0; j<m_br; j++)
            for(k=0; k<m_ar; k++)
                phc[i*m_ar + k] += pha[i*m_ar + j] * phb[j*m_br + k];

    Time2 = clock();
    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
    cout << st;

    // display 10 elements of the result matrix to verify correctness
    cout << "Result matrix: " << endl;
    for (i = 0; i < min(10, m_ar * m_br); i++) {
        cout << phc[i] << " ";
        if ((i + 1) % m_br == 0)
            cout << endl;
    }
    cout << endl;

    free(pha);
    free(phb);
    free(phc);

}

// add code here for block x block matriz multiplication
void OnMultBlock(int m_ar, int m_br, int bkSize)
{
    // parameter validation
    if(!(bkSize <= m_ar && bkSize <= m_br)){
        printf("Invalid block size - it has to be less than or equal to the matrix dimensions!");
        exit(1);
    }
    
    SYSTEMTIME Time1, Time2;

    char st[100];
    double temp;
    int i, j, k;

    double *pha, *phb, *phc;

    pha = (double *)malloc((m_ar * m_br) * sizeof(double));
    phb = (double *)malloc((m_ar * m_br) * sizeof(double));
    phc = (double *)malloc((m_ar * m_br) * sizeof(double));

    // initialize matrix a - identity
    for (i = 0; i < m_ar; i++)
        for (j = 0; j < m_ar; j++)
            pha[i * m_ar + j] = (double)1.0;

    // initialize matrix b - each row is filled with its index + 1
    for (i = 0; i < m_br; i++)
        for (j = 0; j < m_br; j++)
            phb[i * m_br + j] = (double)(i+1); 

    Time1 = clock();

    for(int a = 0; a<m_ar; a+=bkSize) for(int b = 0; b< m_br; b+=bkSize)
            for(int c = 0; c<m_ar; c+=bkSize) for(int d = 0; d<bkSize; d++)
                    for(int e=0; e<bkSize; e++) for(int f=0; f<bkSize; f++)
                            phc[(a+d)*m_ar+b+f] += pha[(a+d)*m_ar+c+e] * phb[(c+e)*m_br+b+f];    

    Time2 = clock();

    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2-Time1)/CLOCKS_PER_SEC);
    cout << st;

    // display 10 elements of the result matrix to verify correctness
    cout << "Result matrix:" << endl;

    for(i = 0; i<min(10, m_br); i++) cout << phc[i] << " ";
    cout << endl;

    free(pha);
    free(phb); 
    free(phc); 
}

void OnMultLineP1(int m_ar, int m_br) {
    /*SYSTEMTIME Time1, Time2;

    char st[100];
    double temp;
    int i, j, k;

    double *pha, *phb, *phc;

    pha = (double *)malloc((m_ar * m_br) * sizeof(double));
    phb = (double *)malloc((m_ar * m_br) * sizeof(double));
    phc = (double *)malloc((m_ar * m_br) * sizeof(double));

    // initialize matrix a - identity
    for (i = 0; i < m_ar; i++)
        for (j = 0; j < m_br; j++)
            pha[i * m_ar + j] = (double)1.0;

    // initialize matrix b - each row is filled with its index + 1
    for (i = 0; i < m_ar; i++)
        for (j = 0; j < m_br; j++)
            phb[i * m_br + j] = (double)(i + 1); 

    Time1 = clock();
    double start = omp_get_wtime();

    #pragma omp parallel for private(i,j,k)
    for(i=0; i<m_ar; i++)
        for(j=0; j<m_br; j++)
            for(k=0; k<m_ar; k++)
                phc[i*m_ar + k] += pha[i*m_ar + j] * phb[j*m_br + k];
    
    double end = omp_get_wtime();
    printf("OMP time - %f seconds\n", end-start);
    Time2 = clock();
    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
    cout << st;

    // display 10 elements of the result matrix to verify correctness
    cout << "Result matrix: " << endl;
    for (i = 0; i < min(10, m_ar * m_br); i++) {
        cout << phc[i] << " ";
        if ((i + 1) % m_br == 0)
            cout << endl;
    }
    cout << endl;

    free(pha);
    free(phb);
    free(phc);
    */
}

void OnMultLineP2(int m_ar, int m_br) {
    /*SYSTEMTIME Time1, Time2;

    char st[100];
    double temp;
    int i, j, k;

    double *pha, *phb, *phc;

    pha = (double *)malloc((m_ar * m_br) * sizeof(double));
    phb = (double *)malloc((m_ar * m_br) * sizeof(double));
    phc = (double *)malloc((m_ar * m_br) * sizeof(double));

    // initialize matrix a - identity
    for (i = 0; i < m_ar; i++)
        for (j = 0; j < m_br; j++)
            pha[i * m_ar + j] = (double)1.0;

    // initialize matrix b - each row is filled with its index + 1
    for (i = 0; i < m_ar; i++)
        for (j = 0; j < m_br; j++)
            phb[i * m_br + j] = (double)(i + 1); 

    Time1 = clock();
    double start = omp_get_wtime();

    #pragma omp parallel for private(i,k,j)
    for(i=0; i<m_ar; i++)
        for(j=0; j<m_ar; j++)
            #pragma omp for
            for(k=0; k<m_br; k++)
                phc[i*m_ar + k] += pha[i*m_ar + j] * phb[j*m_br + k];
    
    double end = omp_get_wtime();
    printf("OMP time - %f seconds\n", end-start);
    Time2 = clock();
    sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
    cout << st;

    // display 10 elements of the result matrix to verify correctness
    cout << "Result matrix: " << endl;
    for (i = 0; i < min(10, m_ar * m_br); i++) {
        cout << phc[i] << " ";
        if ((i + 1) % m_br == 0)
            cout << endl;
    }
    cout << endl;

    free(pha);
    free(phb);
    free(phc);
*/
}


void handle_error (int retval)
{
    printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
    exit(1);
}

void init_papi() {
    int retval = PAPI_library_init(PAPI_VER_CURRENT);
    if (retval != PAPI_VER_CURRENT && retval < 0) {
        printf("PAPI library version mismatch!\n");
        exit(1);
    }
    if (retval < 0) handle_error(retval);

    std::cout << "PAPI Version Number: MAJOR: " << PAPI_VERSION_MAJOR(retval)
              << " MINOR: " << PAPI_VERSION_MINOR(retval)
              << " REVISION: " << PAPI_VERSION_REVISION(retval) << "\n";
}


int main (int argc, char *argv[])
{

    char c;
    int lin, col, blockSize;
    int op;

    int EventSet = PAPI_NULL;
    long long values[2];
    int ret;


    ret = PAPI_library_init( PAPI_VER_CURRENT );
    if ( ret != PAPI_VER_CURRENT )
        std::cout << "FAIL" << endl;


    ret = PAPI_create_eventset(&EventSet);
    if (ret != PAPI_OK) cout << "ERROR: create eventset" << endl;


    ret = PAPI_add_event(EventSet,PAPI_L1_DCM );
    if (ret != PAPI_OK) cout << "ERROR: PAPI_L1_DCM" << endl;


    ret = PAPI_add_event(EventSet,PAPI_L2_DCM);
    if (ret != PAPI_OK) cout << "ERROR: PAPI_L2_DCM" << endl;


    op=1;
    do {
        cout << endl << "1. Multiplication" << endl;
        cout << "2. Line Multiplication" << endl;
        cout << "3. Block Multiplication" << endl;
        cout << "4. Parallel Line Multiplication [1]" << endl;
        cout << "5. Parallel Line Multiplication [2]" << endl;
        cout << "Selection?: ";
        cin >>op;
        if (op == 0)
            break;
        printf("Dimensions: lins=cols ? ");
        cin >> lin;
        col = lin;


        // Start counting
        ret = PAPI_start(EventSet);
        if (ret != PAPI_OK) cout << "ERROR: Start PAPI" << endl;

        switch (op){
            case 1:
                OnMult(lin, col);
                break;
            case 2:
                OnMultLine(lin, col);
                break;
            case 3:
                cout << "Block Size? ";
                cin >> blockSize;
                OnMultBlock(lin, col, blockSize);
                break;
            case 4:
                OnMultLineP1(lin, col);
                break;
            case 5:
                OnMultLineP2(lin, col);
                break;
        }

        ret = PAPI_stop(EventSet, values);
        if (ret != PAPI_OK) cout << "ERROR: Stop PAPI" << endl;
        printf("L1 DCM: %lld \n",values[0]);
        printf("L2 DCM: %lld \n",values[1]);

        ret = PAPI_reset( EventSet );
        if ( ret != PAPI_OK )
            std::cout << "FAIL reset" << endl;



    }while (op != 0);

    ret = PAPI_remove_event( EventSet, PAPI_L1_DCM );
    if ( ret != PAPI_OK )
        std::cout << "FAIL remove event" << endl;

    ret = PAPI_remove_event( EventSet, PAPI_L2_DCM );
    if ( ret != PAPI_OK )
        std::cout << "FAIL remove event" << endl;

    ret = PAPI_destroy_eventset( &EventSet );
    if ( ret != PAPI_OK )
        std::cout << "FAIL destroy" << endl;

}