#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <sstream>
#include <complex>;
using namespace std;

//checking function
int check(string input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (!(input[i] >= 48 && input[i] <= 57) && input[i] != '[' && input[i] != ';' && input[i] != ' ' && input[i] != ']' && input[i] != '.' && input[i] != '-' &&input[i]!='+'&&input[i]!='i')
		{
			cout << "ERROR";
			return 0;
		}
	}

	return 1;
}

//parcing & converting function
vector <vector <complex<float> > > parcing(string input1, float& rows1, float& columns1, int& flagsize)
{
	//initilizing variables of mat1
	vector <vector <complex <float> > > mat1;
	vector <float> data1real , data1imag;
	float spaces1 = 0, semicolons1 = 0;

	//converting & parcing of input1
	  //loop on each element in it
	for (int n = 0; n < input1.length(); n++)
	{
		//element is string which will be converted
		string element;
		float elemreal, elemimag;

		// start & end are the limits which contains numbers inbetween
		int start1, end1;

		//getting start
		if (input1[n] == '[' || input1[n] == ' ' || input1[n] == ';')
		{
			start1 = n + 1;

			//loop to get end
			for (int b = (n + 1); b < input1.length(); b++)
			{
				if (input1[b] == ';' || input1[b] == ']' || input1[b] == ' ')
				{
					end1 = b - 1;
					break;
				}
			}

			//filling element
			element = input1.substr(start1, (end1 - (start1 - 1)));
			int flag = 1;
			for (int i = 1; i < element.length(); i++)
			{
				if(element[i]=='-')
				{
					flag = 0;
					break;
				}
			}
			int signindex ;
			signindex=element.find('+', 1);
			if (flag== 0)
			{
				signindex = element.find('-', 1);
			}

			elemreal = atof((element.substr(0,signindex)).c_str());
			elemimag = atof((element.substr(signindex)).c_str());
			data1real.push_back(elemreal);
			data1imag.push_back(elemimag);
		}
		//counting spaces & semi colons
		if (input1[n] == ';')
		{
			semicolons1++;
		}
	}
	//calculating no of rows & columns for mat1
	for (int n = 0; input1[n] != ';'; n++)
	{
		if (input1[n] == ' ')
		{
			spaces1++;
		}
	}
	columns1 = spaces1 + 1;
	rows1 = semicolons1 + 1;

	//filling mat1
	  //m1 is itterator for data1
	int m1 = 0;
	for (int i1 = 0; i1 < rows1; i1++)
	{
		mat1.push_back(vector<complex<float> >());
		for (int j1 = 0; j1 < columns1; j1++)
		{ 
			complex <float> comp(data1real[m1], data1imag[m1]);
			mat1[i1].push_back(comp);
			m1++;
		}
	}
	flagsize = 0;
	int sumsizemat1 = 0;
	for (int i = 0; i < mat1.size(); i++)
	{
		sumsizemat1 += mat1[i].size();
	}
	if (sumsizemat1 != data1real.size())
		flagsize = 1;
	return mat1;
}

//printing function
void matprint(vector<vector <complex<float> > > mat)
{
	//loop to print the sum
	cout << '[';
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[0].size(); j++)
		{
			cout << real(mat[i][j]);
			if (imag(mat[i][j]) >= 0)
			{
				cout << '+' << imag(mat[i][j])<<'i';
			}
			else
			{
				cout << imag(mat[i][j])<<'i';
			}
			if (j != (mat[0].size() - 1))
				cout << " ";
		}
		if (i != (mat.size() - 1))
			cout << ';';
	}
	cout << ']';
}

//summation function
vector <vector <complex< float> > > sum(vector<vector <complex<float> > >& mat1, vector<vector<complex<float> > >& mat2)
{
	//initializing returning vector
	vector<vector<complex<float> > > matsum;

	//loop to sum
	for (int i = 0; i < mat1.size(); i++)
	{
		matsum.push_back(vector <complex<float> >());
		for (int j = 0; j < mat1[0].size(); j++)
		{
			matsum[i].push_back(mat1[i][j] + mat2[i][j]);
		}
	}
	return matsum;
}

//difference function
vector <vector<complex <float> > > diff(vector <vector<complex <float> > >& mat1, vector <vector<complex <float> > >& mat2)
{
	//initializing returning vector
	vector <vector<complex <float> > > matdiff;

	//loop to minus
	for (int i = 0; i < mat1.size(); i++)
	{
		matdiff.push_back(vector<complex <float> >());
		for (int j = 0; j < mat1[0].size(); j++)
		{
			matdiff[i].push_back(mat1[i][j] - mat2[i][j]);
		}
	}
	return matdiff;
}

//multiplication function
vector <vector<complex <float> > > mult(vector <vector<complex <float> > > mat1, vector <vector<complex <float> > > mat2)
{
	vector <complex<float> > sum;
	vector <vector<complex <float> > > matmult;

	//multiplying matrices & saving results in 1D vector
	for (int r = 0; r < mat1.size(); r++)
	{
		for (int i = 0; i < mat2[0].size(); i++)
		{
			complex<float> result = 0;
			for (int j = 0; j < mat2.size(); j++)
			{
				result += mat1[r][j] * mat2[j][i];
			}
			sum.push_back(result);
		}
	}

	//filling matmult the 2D vector
	int m1 = 0;
	for (int i1 = 0; i1 < mat1.size(); i1++)
	{
		matmult.push_back(vector<complex<float> >());
		for (int j1 = 0; j1 < mat2[0].size(); j1++)
		{
			matmult[i1].push_back(sum[m1]);
			m1++;
		}
	}
	return matmult;
}



int main()
{
	//initlialize variables of inputs
	string input1;
	string input2;
	char operat;
	float rows1;
	float columns1;
	float determ1;
	float rows2;
	float columns2;
	float determ2;
	int flagsize1, flagsize2;
	//initilizing variables of mat2
	vector <vector <complex<float> > > mat2;

	//taking inputs
	getline(cin, input1);

	//checking input1
	int check1 = check(input1);
	if (check1 == 0)
	{
		return 0;
	}
	int p;
	//initilizing variables of mat1
	vector <vector <complex<float> > > mat1;
	//using parcing function
	mat1 = parcing(input1, rows1, columns1, flagsize1);

	cin >> operat;
	if (flagsize1 == 1)
	{
		cout << "ERROR";
		return 0;
	}
	for (int s = 1; s <= mat1.size() - 1; s++)
	{
		if (mat1[s].size() != mat1[s - 1].size())
		{
			cout << "ERROR";
		}
	}


	if (operat == '+' || operat == '-' || operat == '*' || operat == '/')
	{
		cin.ignore();
		getline(cin, input2);

		//checking input2
		int check2 = check(input2);
		if (check2 == 0)
		{
			return 0;
		}


		//using parcing function
		mat2 = parcing(input2, rows2, columns2, flagsize2);

		/*if (rows1 != rows2 || columns1 != columns2||flagsize2==1)
		{
			cout << "ERROR";
			return 0;
		}
		*/

	}

	switch (operat)
	{
	
	default: cout << "ERROR";
		break;
	case '+':
	{
		int flag = 0;
		for (int i = 0; i < mat1.size(); i++)
		{
			if (mat1[i].size() != mat2[i].size())
			{
				flag = 1;
				break;
			}
		}
		if (mat1.size() != mat2.size() || flag == 1)
		{
			cout << "ERROR";

		}
		else
		{
			vector <vector<complex <float> > > matsum;

			//summation of mats
			matsum = sum(mat1, mat2);

			//printing the sum
			matprint(matsum);
			break;
		}
	}
	case '-':
	{
		int flag = 0;
		for (int i = 0; i < mat1.size(); i++)
		{
			if (mat1[i].size() != mat2[i].size())
			{
				flag = 1;
				break;
			}
		}
		if (mat1.size() != mat2.size() || flag == 1)
		{
			cout << "ERROR";
		}
		else
		{
			vector <vector<complex <float> > > matdiff;

			//difference of mats
			matdiff = diff(mat1, mat2);

			//printing the difference
			matprint(matdiff);
			break;
		}
	}
	case '*':
	{
		//flag to check no of columns = no of rows
		int flag = 0;
		for (int i = 0; i < mat1.size(); i++)
		{
			if (mat1[i].size() != mat2.size())
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			cout << "ERROR";
		}
		else
		{
			vector <vector<complex <float> > > matmult;

			//multiplication of mats
			matmult = mult(mat1, mat2);

			//printing the multiplication
			matprint(matmult);

			break;
		}
	}

	}
	return 0;

}
