
/*
    * Ho Chi Minh City University of Technology
    * Faculty of Computer Science and Engineering
    * Initial code for Assignment 0
    * Programming Fundamentals Spring 2021
    * Author: Nguyen Thanh Nhan
    * Date: 08.02.2021
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef firstFight_h
#define firstFight_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
//Giai đoạn chuan bị cho trận chiến
void MG(int& HP, int& M, int x)

{
    switch (x)
    {
    case 1:
        if (M >= 190)
        {
            HP += 5;
            M -= 190;
        }
        break;
    case 2:
        if (M >= 195)
        {
            HP += 7;
            M -= 195;
        }
        break;
    case 3:
        if (M >= 200)
        {
            HP += 9;
            M -= 200;
        }
        break;
    case 4:
        if (M >= 205)
        {
            HP += 11;
            M -= 205;
        }
        break;
    }
}
bool so_nguyen_to(int& a)

{
    int dem(0);
    for (int i(1); i <= a; i++)
        if (a % i == 0) dem++;
    if (dem == 2) return true;
    else return false;
}
void check_dk(int& a)
{
    if (a < 0) a = 0;
    if (a > 1000) a = 1000;
}
int chien_dau(int& HP1, int& HP2,const int &ID1,const int &ID2)
{
    if ((ID1 == 1) && (ID2 == 2))
    {
        return 0;
    }
    if ((ID1 == 1) && (ID2 == 0))
    {
        HP2 = 0;
        return 1;
    }
    if ((ID1 == 0) && (ID2 == 1))
    {
        HP1 = 0;
        return -1;
    }
    if ((ID1 == 0) && (ID2 == 0))
    {
        if (HP1 == HP2)
        {
            return 0;
        }
        else
        {
            int u;
            u = round((2.0 * HP1 * HP2) / (1.0 * (HP1 + HP2)));
            int a;
            a = HP1;
            HP1 -= abs(HP2 - u);
            HP2 -= abs(a - u);
            if (HP1 < HP2) return -1;
            else return 1;
        } 
    } 
    return -1;
}

int getReady(int& HP, const int& ID, int& M, const int& E1)
{
    check_dk(HP);
    check_dk(M);
    //Trường hợp 1  (XONG)
    if ((E1 >= 100) && (E1 <= 199))             
    {
        if (ID == 0) 
        {
            if (((E1 - 100) % 64) < (HP % 100)) 
            {
                if ((M % 2 == 0) && (M >= 200))
                {
                    HP += 25;
                    M -= 200;
                }
                else if ((M % 2 == 1) && (HP > 500) && (M >= 300))
                {
                    HP += 50;
                    M -= 300;
                }
            } 
        } else if(ID==1) HP += (50 + 25);
    }
    //Trường hợp 2  (XONG)
    else if ((E1 >= 200) && (E1 <= 299))        
    {
        int x;
        x = E1 % 4 + 1;
        if ((ID == 1) && (ID == 2))
            MG(HP, M, x);
        if (ID == 0)
        {
            if (((x == 1) || (x == 3)) && (M % 2 == 1))
                MG(HP, M, x);
            if (((x == 2) || (x == 4)) && (M % 2 == 0))
                MG(HP, M, x);
        }
    }
    //Trường hợp 3  (XONG)
    else if ((E1 >= 300) && (E1 >= 399))        
    {
        if (HP >= 600)
        {
            int du(0), a(0);
            du = E1 % 10;
            if (so_nguyen_to(du))
            {
                a = 2 * du;
            }
            else a = 1;
            if (so_nguyen_to(du))
            {
                if (M >= 500)
                {
                    if (ID == 1)
                    {
                        HP += 200;
                        M -= 500;
                    }
                    if ((ID == 0) || (ID == 2))
                    {
                        HP = round(HP * (1 + 2 * a * 0.01));
                        M -= 500;
                    }
                }
            }
            else
            {
                if (M >= 300)
                {
                    HP = round(HP * (1.0 + a * 0.01));
                    M -= 300;
                }
            }

        }
    }
    //Trường hợp 4  (XONG)
    else if ((E1 >= 400) && (E1 <= 499))        
    {
        if (E1 % 5 == 0)
        {
            HP = round(HP * (1 - 0.1));
        }
    }
    //Trường hợp 5  (XONG)
    else if (E1 == 500)                         
    {
        HP = round(HP * 1.0 * (3 / 4));
        M= round(M * 1.0 * (3 / 4));
    }
    //Trường hợp đặt biệt
    else
        return -999;   
    check_dk(HP);
    check_dk(M);
    return HP + M;
}

int firstBattle(int& HP1, int& HP2, const int& ID1, const int& ID2, const int& E2) {
    //Complete this function to gain point on task 2
    int ketqua{};
    if ((E2 >= 100) && (E2 <= 199))
    {
        HP1 = round(HP1 * 1.1);
        HP2 = round(HP2 * 1.3);
        ketqua = chien_dau(HP1, HP2, ID1, ID2);
    }
    if ((E2 >= 200) && (E2 <= 299))
    {
        HP1 = round(HP1 * 1.7);
        HP2 = round(HP2 * 1.2);
        ketqua = chien_dau(HP1, HP2, ID1, ID2);
    }
    if ((E2 >= 300) && (E2 <= 399))
    {
        if (E2 < 350) HP1 += 30;
        else HP1 += (E2 % 100);
        ketqua = chien_dau(HP1, HP2, ID1, ID2);
    }
    if ((E2 >= 400) && (E2 <= 499))
    {
        HP1 = round(HP1 * (1.0 + 0.3));
        HP2 = round(HP2 * (1.0 - 0.2));
        HP1 = round(HP1 * 0.5);
        ketqua = chien_dau(HP1, HP2, ID1, ID2);
    }
    if ((E2 < 100) && (E2 > 499))
    {
        return -999;
    }
    HP1 = round(HP1 * (1.0 - 0.2));
    check_dk(HP1);
    check_dk(HP2);
    return ketqua;
}

int secondBattle(int& HP1, int& HP2, const int& ID1, const int& ID2, const int& E3) {
    //Complete this function to gain point on task 3
    int ketqua;
    HP1 = round(HP1 * 1.4);
    HP2 = round(HP2 * 1.6);
    if ((E3 >= 100) && (E3 <=199))
    {
        int HP1_ao(HP1);
        if (ID2 == 2) 
        {
            ketqua = chien_dau(HP1_ao, HP2, ID1, ID2);
        }
        else
        {
            HP2 = round(HP2 * (1.0 - 0.05));
            ketqua = chien_dau(HP1_ao, HP2, ID1, ID2);
        }
    }
    if ((E3 >= 200) && (E3 <= 299))
    {
        ketqua = 0;
        if (ID2 == 0)
            HP2 = round(HP2 * (1.0 - 0.05));

    }
    if ((E3 < 100) && (E3 > 299))
    {
        return -999;
    }
    check_dk(HP1);
    check_dk(HP2);
    return ketqua;
}

int finalBattle(int& HP1, int& HP2, const int& ID1, const int& ID2, const int& E4) {
    //Complete this function to gain point on task 4
    int ketqua;
    if ((E4 >= 100) && (E4 <= 199))
    {
        ketqua = 0;
        if (ID2 == 2)
            HP2 = round(HP2 * 0.3);
        else HP2 = round(HP2 * 0.1);
    }
    if ((E4 >= 200) && (E4 <= 299))
    {
        HP2 = 0;
        ketqua = 1;
    }
    if ((E4 < 100) && (E4 > 299))
    {
        return -999;
    }
    return ketqua;
}
////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* firstFight_h */
