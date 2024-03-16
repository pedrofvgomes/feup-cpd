package proj1;

import java.util.Scanner;

public class MatrixProduct {
    public static void main(String[] args) {
        int choice;
        Scanner scanner = new Scanner(System.in);

        do{
            System.out.println("1. Multiplication\n2. Line Multiplication\n3. Block Multiplication");
            System.out.print("Selection?: ");
            choice = scanner.nextInt();

            if(choice == 0) break;

            System.out.print("Enter the number of rows and columns: ");
            int m_ar = scanner.nextInt();

            MatrixProduct mp = new MatrixProduct();

            switch (choice) {
                case 1:
                    mp.onMult(m_ar, m_ar);
                    break;
                case 2:
                    mp.onMultLine(m_ar, m_ar);
                default:
                    break;
            }

        }while(choice!=0);

        scanner.close();
    }

    public void onMult(int m_ar, int m_br) {
        // timers, to be set later
        long startTime, endTime;

        double[] pha = new double[m_ar * m_ar];
        double[] phb = new double[m_ar * m_ar];
        double[] phc = new double[m_ar * m_ar];

        int i, j, k;
        double temp;

        for (i = 0; i < m_ar; i++)
            for (j = 0; j < m_ar; j++)
                pha[i * m_ar + j] = (double) 1.0;

        for (i = 0; i < m_br; i++)
            for (j = 0; j < m_br; j++)
                phb[i * m_br + j] = (double) (i + 1);

        // start timer
        startTime = System.currentTimeMillis();

        for (i = 0; i < m_ar; i++) {
            for (j = 0; j < m_br; j++) {
                temp = 0;
                for (k = 0; k < m_ar; k++) {
                    temp += pha[i * m_ar + k] * phb[k * m_br + j];
                }
                phc[i * m_ar + j] = temp;
            }
        }

        // end timer
        endTime = System.currentTimeMillis();

        // print time
        System.out.println("Time: " + (double) (endTime - startTime) + " ms");

        String output = "";

        // print 10 elements of the result matrix
        for (i = 0; i < 1; i++)
            for (j = 0; j < Math.min(10, m_br); j++)
                output += phc[j] + " ";

        System.out.println(output);
    }

    public void onMultLine(int m_ar, int m_br) {
        // timers, to be set later
        long startTime, endTime;

        double[] pha = new double[m_ar * m_ar];
        double[] phb = new double[m_ar * m_ar];
        double[] phc = new double[m_ar * m_ar];

        int i, j, k;

        for (i = 0; i < m_ar; i++)
            for (j = 0; j < m_ar; j++)
                pha[i * m_ar + j] = (double) 1.0;

        for (i = 0; i < m_br; i++)
            for (j = 0; j < m_br; j++)
                phb[i * m_br + j] = (double) (i + 1);

        // start timer
        startTime = System.currentTimeMillis();

        for (i = 0; i < m_ar; i++)
            for (j = 0; j < m_br; j++)
                for (k = 0; k < m_ar; k++)
                    phc[i * m_ar + k] += pha[i * m_ar + j] * phb[j * m_br + k];

        // end timer
        endTime = System.currentTimeMillis();

        // print time
        System.out.println("Time: " + (double) (endTime - startTime) + " ms");

        String output = "";

        // print 10 elements of the result matrix
        for (i = 0; i < Math.min(10, m_ar * m_br); i++) 
            output += phc[i];

        System.out.println(output);
    }
}
