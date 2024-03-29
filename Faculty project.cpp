#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

//checking function
int check(string input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (!(input[i] >= 48 && input[i] <= 57) && input[i] != '[' && input[i] != ';' && input[i] != ' ' && input[i] != ']' && input[i] != '.' && input[i] != '-')
		{
			cout << "ERROR";
			return 0;
		}
	}

	return 1;
}

//parcing & converting function
vector <vector< float> > parcing(string input1, float& rows1, float& columns1, int& flagsize)
{
	//initilizing variables of mat1
	vector <vector <float> > mat1;
	vector <float> data1;
	float spaces1 = 0, semicolons1 = 0;

	//converting & parcing of input1
	  //loop on each element in it
	for (int n = 0; n < input1.length(); n++)
	{
		//element is string which will be converted
		string element;
		float elem;

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
			elem = atof(element.c_str());
			data1.push_back(elem);

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
		mat1.push_back(vector<float>());
		for (int j1 = 0; j1 < columns1; j1++)
		{
			mat1[i1].push_back(data1[m1]);
			m1++;
		}
	}
	flagsize = 0;
	int sumsizemat1 = 0;
	for (int i = 0; i < mat1.size(); i++)
	{
		sumsizemat1 += mat1[i].size();
	}
	if (sumsizemat1 != data1.size())
		flagsize = 1;
	return mat1;
}

//printing function
void matprint(vector<vector<float> > mat)
{
	//loop to print the sum
	cout << '[';
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[0].size(); j++)
		{
			cout << mat[i][j];
			if (j != (mat[0].size() - 1))
				cout << " ";
		}
		if (i != (mat.size() - 1))
			cout << ';';
	}
	cout << ']';
}

//summation function
vector <vector< float> > sum(vector<vector<float> >& mat1, vector<vector<float> >& mat2)
{
	//initializing returning vector
	vector<vector<float> > matsum;

	//loop to sum
	for (int i = 0; i < mat1.size(); i++)
	{
		matsum.push_back(vector<float>());
		for (int j = 0; j < mat1[0].size(); j++)
		{
			matsum[i].push_back(mat1[i][j] + mat2[i][j]);
		}
	}
	return matsum;
}

//difference function
vector <vector< float> > diff(vector<vector<float> >& mat1, vector<vector<float> >& mat2)
{
	//initializing returning vector
	vector <vector< float> > matdiff;

	//loop to minus
	for (int i = 0; i < mat1.size(); i++)
	{
		matdiff.push_back(vector<float>());
		for (int j = 0; j < mat1[0].size(); j++)
		{
			matdiff[i].push_back(mat1[i][j] - mat2[i][j]);
		}
	}
	return matdiff;
}

//multiplication function
vector<vector<float> > mult(vector<vector<float> > mat1, vector<vector<float> > mat2)
{
	vector <float> sum;
	vector <vector<float> > matmult;

	//multiplying matrices & saving results in 1D vector
	for (int r = 0; r < mat1.size(); r++)
	{
		for (int i = 0; i < mat2[0].size(); i++)
		{
			float result = 0;
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
		matmult.push_back(vector<float>());
		for (int j1 = 0; j1 < mat2[0].size(); j1++)
		{
			matmult[i1].push_back(sum[m1]);
			m1++;
		}
	}
	return matmult;
}

//power function
vector <vector< float> > power(vector <vector< float> >& mat1, int p)
{
	vector <vector< float> > matpow;
	matpow = mat1;
	for (int i = 1; i < p; i++)
	{
		matpow = mult(matpow, mat1);
	}
	return matpow;
}

//transpose function
vector <vector< float> > transpose(vector <vector< float> >& mat1, float& rows1, float& columns1)
{
	vector <vector< float> > mattransp;

	//filling mattransp
	for (int i1 = 0; i1 < columns1; i1++)
	{
		mattransp.push_back(vector<float>());
		for (int j1 = 0; j1 < rows1; j1++)
		{
			mattransp[i1].push_back(0);
		}
	}
	for (int i1 = 0; i1 < columns1; i1++)
	{
		for (int j1 = 0; j1 < rows1; j1++)
		{

			mattransp[i1][j1] = mat1[j1][i1];
		}
	}

	return mattransp;
}

//determinant function
float determinant(vector <vector< float> > mat1, float rows1, float columns1)
{
	float determ1 = 1;
	//check that the main diagonal does not contain zero
	for (int s = 0; s < rows1; s++)
	{
		//swapping the row which contain zero
		if (mat1[s][s] == 0)
		{
			determ1 *= -1;
			vector <float> swapmat;
			//saving row in another vector
			for (int i = 0; i < columns1; i++)
			{
				swapmat.push_back(mat1[s][i]);
			}
				//check if it is the last row or not to avoid assertion failed
				if (s != columns1 - 1)
				{
					for(int j=s+1 ;j<rows1;j++)
					{
						//check that the other row does not contain zero in the main diagonal
						if (mat1[j][s] != 0)
						{
							//loop to swap the rows
							for (int i = 0; i < columns1; i++)
							{
								mat1[s][i] = mat1[j][i];
								mat1[j][i] = swapmat[i];
							}
							break;
						}
					}
				}
				//condition for the row if it was the last in the matrix
				else
				{
					for (int j = 0; j < rows1-1; j++)
					{
						if (mat1[j][s] != 0)
						{
							for (int i = 0; i < columns1; i++)
							{
								mat1[s][i] = mat1[j][i];
								mat1[j][i] = swapmat[i];
							}
						}
						break;
					}
				}
		}
	}
	//iterrations on columns to make lower triangular matrix
	for (int j = 0; j < (columns1 - 1); j++)
	{
		//iterations on rows to make lower triangular matrix
		for (int i = j + 1; i < rows1; i++)
		{

			if (mat1[i][j] == 0)
			{
				continue;
			}
			//get the number which will be multiplyed with the row
			float multnum1 = mat1[i][j]/mat1[j][j];
			
			//itteration to fill the new row with zero
			for (int c = 0; c < columns1; c++)
			{
				float z = ( mat1[i][c]) - (multnum1 * mat1[j][c]);
				mat1[i][c] = z;
			}
		}
	}

	//iteration to get determinant by multiplying elements of main diagonal
	for (int i = 0; i < rows1; i++)
	{
		determ1 *= mat1[i][i];
	}
	return determ1;
}

//inverse function
vector <vector< float> > matinverse(vector <vector< float> > mat1, float rows1, float columns1)
{
	if (determinant(mat1, rows1, columns1) == 0)
	{
		cout << "ERROR";
		exit(1);
	}
	float invdetermofmat1 = 1 / determinant(mat1, rows1, columns1);

	//adjoint matrix
	vector <vector< float> > adjointmat;
	//iteration to fill adjointmat
	for (int i = 0; i < rows1; i++)
	{
		adjointmat.push_back(vector <float>());
		for (int j = 0; j < columns1; j++)
		{
			int rc = -1;
			float adjelement;
			vector <vector< float> > matc;
			//iteration to fill matc (the inner determinant)
			for (int r = 0; r < rows1; r++)
			{
				if (r == i)
				{
					continue;
				}
				matc.push_back(vector <float>());
				rc++;
				for (int c = 0; c < columns1; c++)
				{
					if (c == j)
					{
						continue;
					}
					matc[rc].push_back(mat1[r][c]);
				}
			}
			//calculating elements of adjointmat
			adjelement = (pow(-1, (i + 1) + (j + 1))) * determinant(matc, (rows1 - 1), (columns1 - 1));
			adjointmat[i].push_back(adjelement);
		}
	}
	//calculating the transpose of adjointmat
	vector <vector< float> > transposeadjointmat;
	transposeadjointmat = transpose(adjointmat, rows1, columns1);
	//calculating matrix inverse
	vector <vector< float> > matinver;

	//iteration to fill matinver
	for (int i = 0; i < rows1; i++)
	{
		matinver.push_back(vector <float>());
		for (int j = 0; j < columns1; j++)
		{
			matinver[i].push_back(invdetermofmat1 * transposeadjointmat[i][j]);
		}
	}

	return matinver;
}

//division function
vector <vector< float> > division(vector<vector<float> > mat1, vector<vector<float> > mat2, float rows2, float columns2)
{
	vector <vector< float> >matdivision;
	vector <vector< float> >mat2inv;
	mat2inv = matinverse(mat2, rows2, columns2);

	matdivision = mult(mat1, mat2inv);

	return matdivision;
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
	vector <vector <float> > mat2;

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
	vector <vector <float> > mat1;
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
			vector <vector< float> > matsum;

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
			vector <vector< float> > matdiff;

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
			vector <vector<float> > matmult;

			//multiplication of mats
			matmult = mult(mat1, mat2);

			//printing the multiplication
			matprint(matmult);

			break;
		}
	}
	case '^':
	{
		cin >> p;
		if (p < 0 || (int)p != p || rows1 != columns1)
		{
			cout << "ERROR";
			return 0;
		}
		else
		{
			vector <vector< float> > matpow;

			//power operation
			matpow = power(mat1, p);

			//printing power
			matprint(matpow);
			return 0;
		}
		break;
	}
	case 'T':
	{
		vector <vector< float> >mattransp;

		//transpose operation
		mattransp = transpose(mat1, rows1, columns1);

		//printing transpose
		matprint(mattransp);
		break;
	}
	case 'D':
	{
		//condition for square matrix
		if (rows1 != columns1)
		{
			cout << "ERROR";
			return 0;
		}
		else
		{
			determ1 = determinant(mat1, rows1, columns1);
			cout << determ1;
		}
		break;
	}
	case 'I':
	{
		//condition for square matrix
		if (rows1 != columns1)
		{
			cout << "ERROR";
			return 0;
		}
		else
		{
			vector <vector< float> >matinv;

			//inverse operation
			matinv = matinverse(mat1, rows1, columns1);

			//printing inverse
			matprint(matinv);

		}
		break;
	}
	case '/':
	{
		if (rows2 != columns1)
		{
			cout << "ERROR";
			return 0;
		}
		else
		{
			vector <vector< float> >matdivision;

			matdivision = division(mat1, mat2, rows2, columns2);

			matprint(matdivision);
		}
		break;
	}
	}
	return 0;

}
