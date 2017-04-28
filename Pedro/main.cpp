#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <string>

using namespace std;

void ClearScreen();
bool SetWindow(int,int);

// Alterar as variaveis GlobalWidth e GlobalHeight para o valor pretendido
// Se nao pretender alterar o tamanho da janela alterar a variavel ChangeWindowSize para 0

void ClearScreen();
bool SetWindow(int, int);

int GlobalWidth = 200; // 120 ate 240
int GlobalHeight = 30; // 30 ate 63
bool ChangeWindowSize = 0;

#ifdef _WIN32

#include <windows.h>

void ClearScreen()
{
	SetWindow(GlobalWidth, GlobalHeight);

	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

bool SetWindow(int Width, int Height)
{
	if (ChangeWindowSize)
	{
		_COORD coord;
		coord.X = Width;
		coord.Y = Height;

		_SMALL_RECT Rect;
		Rect.Top = 0;
		Rect.Left = 0;
		Rect.Bottom = Height - 1;
		Rect.Right = Width - 1;

		// Get handle of the standard output 
		HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
		if (Handle == NULL)
		{
			cout << "Failure in getting the handle\n" << GetLastError();
			return FALSE;
		}

		// Set screen buffer size to that specified in coord 
		if (!SetConsoleScreenBufferSize(Handle, coord))
		{
			cout << "Failure in setting buffer size\n" << GetLastError();
			return FALSE;
		}

		// Set the window size to that specified in Rect 
		if (!SetConsoleWindowInfo(Handle, TRUE, &Rect))
		{
			cout << "Failure in setting window size\n" << GetLastError();
			return FALSE;
		}
	}
	return TRUE;

}

#else


void ClearScreen()
{
	SetWindow(GlobalWidth, GlobalHeight);

	std::cout << "\033[2J\033[1;1H";
	std::cout << "\033[2J\033[1;1H";
	}

bool SetWindow(int width, int height)
{
	if (ChangeWindowSize)
	{
		string res = "\e[8;";
		res += to_string(height);
		res += ";";
		res += to_string(width);
		res += "t";
		cout << res;

	}
	return true;
}

#endif


// Estruturas do programa :-)
/*struct paragem
{
string nome;
};*/

struct linha
{
	int ID;
	int freq;
	vector<string> paragens;
	vector<int> tempoviagem;

};
vector<linha> LinhasGlobais;

struct condutor
{
	int ID;
	string nome;
	int HorasTurno;
	int HorasSemanais;
	int HorasDescanco;

};
vector<condutor> CondutoresGlobais;

fstream linhasfile("linhas", fstream::in | fstream::out);

fstream condutoresfile("condutores", fstream::in | fstream::out);

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

// Retorna um string com n espacos
string addspaces(const int &n)
{
	string res;
	for (int i = 0; i < n; ++i)
	{
		res += " ";
	}

	return res;
}

// Remove os espacos no inicio e no final da string
void erasespaces(string &input)
{
	while (input[0] == ' ')
		input.erase(input.begin());

	while (input.back() == ' ')
		input.erase(input.end() - 1);
}


bool is_numeric(string input)
{
	if (input.size() == 0)
		return false;

	erasespaces(input);

	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] < '0' || input[i] > '9')
			return false;
	}

	return true;
}

// Calcula o comprimento de um inteiro
int intsize(int input)
{
	int res = 0;

	while (input)
	{
		res++;
		input /= 10;
	}

	return res;
}

// Prototipos dos menus com o intuito de poder intrecalar entre eles
void MainMenu();
void Menu1();
void Menu1para1();
void Menu1para3();
void Menu2();
void Menu2para1();
void Menu2para3();
void Menu3();
void Menu3para1();
void Menu3para2();
void Menu4();


// Escreve o banner ascii do ficheiro ascii.txt
void PrintBanner()
{
	ifstream banner("ascii.txt", fstream::in);

	cout << "\n";
	string asciiTemp;

	while (getline(banner, asciiTemp))
		cout << addspaces((110 - asciiTemp.size()) / 2) << asciiTemp << "\n";

	cout << "\n\n\n";
}


// Carrega o ficheiro linhas para a veriavel LinhasGlobais
void LoadLinhas()
{
	LinhasGlobais.resize(0);

	string tempstr;
	linha templinha;
	vector<string> paragens;
	vector<int> tempoviagem;

	int selectioncounter = 0;

	while (getline(linhasfile, tempstr))
	{
		selectioncounter = 0;

		tempstr += ';';
		stringstream ss(tempstr);
		string newtempstr;
		paragens.resize(0);
		tempoviagem.resize(0);

		while (getline(ss, newtempstr, ';'))
		{

			if (selectioncounter == 0)
			{
				templinha.ID = stoi(newtempstr);
			}

			if (selectioncounter == 1)
			{
				templinha.freq = stoi(newtempstr);
			}

			if (selectioncounter == 2)
			{
				string newnewtempstr;
				stringstream ss1(newtempstr);

				while (getline(ss1, newnewtempstr, ','))
				{
					erasespaces(newnewtempstr);
					paragens.push_back(newnewtempstr);
				}

				templinha.paragens = paragens;
			}

			if (selectioncounter == 3)
			{
				string newnewtempstr = " ";
				stringstream ss1(newtempstr);

				while (getline(ss1, newnewtempstr, ','))
				{
					tempoviagem.push_back(stoi(newnewtempstr));
				}

				templinha.tempoviagem = tempoviagem;
			}

			selectioncounter++;
		}

		LinhasGlobais.push_back(templinha);
	}

}


// Loading of LinhasGlobais
void LoadCondutores()
{
	CondutoresGlobais.resize(0);

	string tempstr;
	condutor tempcondutor;
	string nome;

	int selectioncounter = 0;

	while (getline(condutoresfile, tempstr))
	{
		selectioncounter = 0;

		tempstr += ';';
		stringstream ss(tempstr);
		string newtempstr;

		while (getline(ss, newtempstr, ';'))
		{

			if (selectioncounter == 0)
			{
				tempcondutor.ID = stoi(newtempstr);
			}

			if (selectioncounter == 1)
			{
				erasespaces(newtempstr);
				tempcondutor.nome = newtempstr;
			}

			if (selectioncounter == 2)
			{
				tempcondutor.HorasTurno = stoi(newtempstr);
			}

			if (selectioncounter == 3)
			{
				tempcondutor.HorasSemanais = stoi(newtempstr);
			}

			if (selectioncounter == 4)
			{
				tempcondutor.HorasDescanco = stoi(newtempstr);
			}

			selectioncounter++;
		}

		CondutoresGlobais.push_back(tempcondutor);
	}

}

//Guarda linhas em memoria e em ficheiro
void SaveLinhas()
{
	remove("linhas");
	ofstream testfile("linhas", fstream::out);

	string linhaparaficheiro;

	for (int i = 0; i < LinhasGlobais.size(); ++i)
	{
		linhaparaficheiro.resize(0);

		linhaparaficheiro += to_string(LinhasGlobais[i].ID);
		linhaparaficheiro += " ; ";
		linhaparaficheiro += to_string(LinhasGlobais[i].freq);
		linhaparaficheiro += " ; ";

		for (int j = 0; j < LinhasGlobais[i].paragens.size() - 1; ++j)
		{
			linhaparaficheiro += LinhasGlobais[i].paragens[j];
			linhaparaficheiro += ", ";
		}

		linhaparaficheiro += LinhasGlobais[i].paragens.back();
		linhaparaficheiro += " ; ";

		for (int j = 0; j < LinhasGlobais[i].tempoviagem.size() - 1; ++j)
		{
			linhaparaficheiro += to_string(LinhasGlobais[i].tempoviagem[j]);
			linhaparaficheiro += ", ";
		}
		linhaparaficheiro += to_string(LinhasGlobais[i].tempoviagem.back());

		testfile << linhaparaficheiro;

		if (i < LinhasGlobais.size() - 1)
			testfile << "\n";
	}

	testfile.close();
}

// Guarda condutores em memoria e em ficheiro
void SaveCondutores()
{
	remove("condutores");
	ofstream testfile("condutores", fstream::out);

	string condutorparaficheiro;

	for (int i = 0; i < CondutoresGlobais.size(); ++i)
	{
		condutorparaficheiro.resize(0);

		condutorparaficheiro += to_string(CondutoresGlobais[i].ID);
		condutorparaficheiro += " ; ";

		condutorparaficheiro += CondutoresGlobais[i].nome;
		condutorparaficheiro += " ; ";

		condutorparaficheiro += to_string(CondutoresGlobais[i].HorasTurno);
		condutorparaficheiro += " ; ";

		condutorparaficheiro += to_string(CondutoresGlobais[i].HorasSemanais);
		condutorparaficheiro += " ; ";

		condutorparaficheiro += to_string(CondutoresGlobais[i].HorasDescanco);

		testfile << condutorparaficheiro;

		if (i < CondutoresGlobais.size() - 1)
			testfile << "\n";
	}

	testfile.close();
}


void MainMenu()
{
	ClearScreen();
	PrintBanner();

	cout << "1- Gestao de linhas\n";
	cout << "2- Gestao de condutores\n";
	cout << "3- Tabelas de informacoes\n";
	cout << "4- Planear viagem\n";
	cout << "0- Encerrar programa\n";
	cout << "\n";

	string input;

	while (1)
	{
		cout << "Selecione uma opcao: ";

		getline(cin, input);
		cout << "\n";

		if (input == "1")
		{
			Menu1();
			break;
		}

		if (input == "2")
		{
			Menu2();
			break;
		}

		if (input == "3")
		{
			Menu3();
			break;
		}

		if (input == "4")
		{
			Menu4();
			break;
		}

		if (input == "0")
			exit(0);

		cout << "Input invalido\n";

	}

}

void Menu1()
{
	ClearScreen();
	PrintBanner();

	cout << "1- Criar linha\n";
	cout << "2- Alterar linha\n";
	cout << "3- Remover linha\n";
	cout << "9- Voltar atras\n";
	cout << "0- Encerrar programa\n";
	cout << "\n";

	string input;

	while (1)
	{
		cout << "Selecione uma opcao: ";

		getline(cin, input);
		cout << "\n";

		if (input == "1")
		{
			Menu1para1();
			break;
		}

		if (input == "2")
		{
			//Menu1para2();
			break;
		}

		if (input == "3")
		{
			Menu1para3();
			break;
		}

		if (input == "9")
		{
			MainMenu();
			break;
		}


		if (input == "0")
			exit(0);

		cout << "Input invalido\n";

	}

}

// Criar linha
void Menu1para1()
{
	ClearScreen();
	PrintBanner();

	string newtempstr;
	linha templinha;
	string tempstr;
	vector<string> paragens;
	vector<int> tempoviagem;


	// Se nao for um numero, pedir novo input
	while (1)
	{
		cout << "\nInsira o ID:";
		getline(cin, tempstr);

		// Condicao para a continuacao do programa
		if (is_numeric(tempstr))
		{
			bool test = 1;
			// Verificar se ja existte alguma linha com o ID igual ao inserido
			for (int i = 0; i < LinhasGlobais.size(); ++i)
			{
				if (LinhasGlobais[i].ID == stoi(tempstr))
				{
					cout << "\nJa exite uma linha com o ID inserido";
					test = 0;
					break;
				}
			}

			if (test)
				break;
		}
		else
		{
			cout << "\nInput invalido!";
		}
	}
	templinha.ID = stoi(tempstr);


	// Se nao for um numero, pedir novo input
	while (1)
	{
		cout << "\nInsira a frequencia da linha:";
		getline(cin, tempstr);

		// Condicao para a continuacao do programa
		if (is_numeric(tempstr))
			break;

		cout << "\nInput invalido!";
	}
	templinha.freq = stoi(tempstr);


	// Se existir algum numero na sequencia, pedir novo input
	while (1)
	{
		paragens.resize(0);

		cout << "\nInsira as paragens separadas por virgulas:";
		getline(cin, tempstr);
		tempstr += ',';

		bool test = 1;

		stringstream ss1(tempstr);
		while (getline(ss1, newtempstr, ','))
		{
			if (is_numeric(newtempstr))
			{
				test = 0;
				break;
			}
			paragens.push_back(newtempstr);
		}

		// Condicao para a continuacao do programa
		if (test && paragens.size() > 1)
			break;
		cout << "\nInput invalido!";
	}
	templinha.paragens = paragens;


	// Se existirem caracteres nao numericos, pedir novo input
	while (1)
	{
		tempoviagem.resize(0);

		cout << "\nInsira os tempos entre paragens, entre virgulas:";
		getline(cin, tempstr);
		tempstr += ',';

		bool test = 1;

		stringstream ss2(tempstr);
		while (getline(ss2, newtempstr, ','))
		{
			if (!is_numeric(newtempstr))
			{
				test = 0;
				break;
			}
			tempoviagem.push_back(stoi(newtempstr));
		}

		// Condicao para a continuacao do programa
		if (test && newtempstr.size() == 0 && tempoviagem.size() == paragens.size() - 1)
			break;

		cout << "\nInput invalido!";
	}

	templinha.tempoviagem = tempoviagem;

	LinhasGlobais.push_back(templinha);

	SaveLinhas();

	cout << "\nLinha Criada, Pressione qualquer tecla para continuar...";

	cin.get();
	Menu1();
}

void Menu1para2()
{
	ClearScreen();
	PrintBanner();

	string tempstr;

	while (1)
	{
		cout << "\nInsira o ID:";
		getline(cin, tempstr);

		// Condicao para a continuacao do programa
		if (is_numeric(tempstr))
		{
			bool test = 1;
			// Verificar se ja existte alguma linha com o ID igual ao inserido
			for (int i = 0; i < LinhasGlobais.size(); ++i)
			{
				if (LinhasGlobais[i].ID == stoi(tempstr))
				{
					cout << "\nJa exite uma linha com o ID inserido";
					test = 0;
					break;
				}
			}

			if (test)
				break;
		}
		else
		{
			cout << "\nInput invalido!";
		}
	}
}

// Remover linha
void Menu1para3()
{
	ClearScreen();
	PrintBanner();

	string tempstr;

	while (1)
	{
		cout << "\nInsira o identificador unico da linha:";
		getline(cin, tempstr);

		// Condicao para a continuacao do programa
		if (is_numeric(tempstr))
		{
			bool test = 0;

			for (int i = 0; i < LinhasGlobais.size(); ++i)
			{
				if (LinhasGlobais[i].ID == stoi(tempstr))
				{
					LinhasGlobais.erase(LinhasGlobais.begin() + i);
					test = 1;
					break;
				}
			}

			if (test)
				break;
			cout << "\nLinha nao encontrada!";
		}
		else
		{
			cout << "\nInput invalido!";
		}
	}

	cout << "\nLinha removida, Pressione qualquer tecla para continuar...";
	cin.get();

	SaveLinhas();
	Menu1();
}

void Menu2()
{
	ClearScreen();
	PrintBanner();

	cout << "1- Criar condutor\n";
	cout << "2- Alterar condutor\n";
	cout << "3- Remover condutor\n";
	cout << "9- Voltar atras\n";
	cout << "0- Encerrar programa\n";
	cout << "\n";

	string input;

	while (1)
	{
		cout << "Selecione uma opcao: ";

		getline(cin, input);
		cout << "\n";

		if (input == "1")
		{
			Menu2para1();
			break;
		}

		if (input == "2")
		{
			//Menu2para2();
			break;
		}

		if (input == "3")
		{
			Menu2para3();
			break;
		}

		if (input == "9")
		{
			MainMenu();
			break;
		}

		if (input == "0")
			exit(0);

		cout << "Input invalido\n";

	}

}

// Criar condutor
void Menu2para1()
{
	ClearScreen();
	PrintBanner();

	condutor tempcondutor;
	string tempstr;

	// Se nao for um numero, pedir novo input
	while (1)
	{
		cout << "\nInsira o ID:";
		getline(cin, tempstr);

		// Condicao para a continuacao do programa
		if (is_numeric(tempstr))
		{
			bool test = 1;
			// Verificar se ja existte algum condutor com o ID igual ao inserido
			for (int i = 0; i < CondutoresGlobais.size(); ++i)
			{
				if (CondutoresGlobais[i].ID == stoi(tempstr))
				{
					cout << "\nJa exite um condutor com o ID inserido";
					test = 0;
					break;
				}
			}

			if (test)
				break;
		}
		else
		{
			cout << "\nInput invalido!";
		}
	}
	tempcondutor.ID = stoi(tempstr);


	// Se nao conter exclusivamente caracteres do alfebeto, pedir novo input
	while (1)
	{
		cout << "\nInsira o nome do condutor:";
		getline(cin, tempstr);

		// Condicao para a continuacao do programa
		if (tempstr.size() > 0 && !is_numeric(tempstr))
			break;

		cout << "\nInput invalido!";
	}
	tempcondutor.nome = tempstr;


	// Se nao for um numero, pedir novo input
	while (1)
	{
		cout << "\nInsira o numero de horas por turno:";
		getline(cin, tempstr);

		// Condicao para a continuacao do programa
		if (is_numeric(tempstr))
			break;

		cout << "\nInput invalido!";
	}
	tempcondutor.HorasTurno = stoi(tempstr);


	// Se nao for um numero, pedir novo input
	while (1)
	{
		cout << "\nInsira o numero de horas semanais:";
		getline(cin, tempstr);

		// Condicao para a continuacao do programa
		if (is_numeric(tempstr))
			break;

		cout << "\nInput invalido!";
	}
	tempcondutor.HorasSemanais = stoi(tempstr);


	// Se nao for um numero, pedir novo input
	while (1)
	{
		cout << "\nInsira o numero de horas de descanco:";
		getline(cin, tempstr);

		// Condicao para a continuacao do programa
		if (is_numeric(tempstr))
			break;

		cout << "\nInput invalido!";
	}
	tempcondutor.HorasDescanco = stoi(tempstr);

	CondutoresGlobais.push_back(tempcondutor);

	SaveCondutores();

	cout << "\nCondutor Criado, Pressione qualquer tecla para continuar...";

	cin.get();
	Menu2();
}

// Remover condutor
void Menu2para3()
{
	ClearScreen();
	PrintBanner();

	string tempstr;

	while (1)
	{
		cout << "\nInsira o identificador unico do condutor:";
		getline(cin, tempstr);

		// Condicao para a continuacao do programa
		if (is_numeric(tempstr))
		{
			bool test = 0;

			for (int i = 0; i < CondutoresGlobais.size(); ++i)
			{
				if (CondutoresGlobais[i].ID == stoi(tempstr))
				{
					CondutoresGlobais.erase(CondutoresGlobais.begin() + i);
					test = 1;
					break;
				}
			}

			if (test)
				break;
			cout << "\nCondutor nao encontrado!";
		}
		else
		{
			cout << "\nInput invalido!";
		}
	}

	cout << "\nCondutor removido, Pressione qualquer tecla para continuar...";
	cin.get();

	SaveCondutores();
	Menu2();
}

// Visualizacao de informacao
void Menu3()
{
	ClearScreen();
	PrintBanner();

	cout << "1- Visualizar linhas\n";
	cout << "2- Visualizar condutores\n";
	cout << "9- Voltar atras\n";
	cout << "0- Encerrar programa\n";
	cout << "\n";
	string input;

	while (1)
	{
		cout << "Selecione uma opcao: ";

		getline(cin, input);
		cout << "\n";

		if (input == "1")
		{
			Menu3para1();
			break;
		}

		if (input == "2")
		{
			Menu3para2();
			break;
		}

		if (input == "9")
		{
			MainMenu();
			break;
		}

		if (input == "0")
		{
			exit(0);
		}

		cout << "Input invalido\n";

	}

}

// Visualizacao de linhas
void Menu3para1()
{
	ClearScreen();
	PrintBanner();

	vector<int> linhas_max{ 2,4,8,20 };
	vector<string> paragensoutput;
	vector<string> temposoutput;
	string paragensstr;
	string temposstr;

	int count = 0;
	for (int i = 0; i < LinhasGlobais.size(); ++i)
	{
		if (intsize(LinhasGlobais[i].ID) > linhas_max[0])
			linhas_max[0] = intsize(LinhasGlobais[i].ID);

		if (intsize(LinhasGlobais[i].freq) > linhas_max[1])
			linhas_max[1] = intsize(LinhasGlobais[i].freq);

		paragensstr.resize(0);
		for (int j = 0; j < LinhasGlobais[i].paragens.size() - 1; ++j)
		{
			paragensstr += LinhasGlobais[i].paragens[j] + ", ";
		}
		paragensstr += LinhasGlobais[i].paragens.back();
		paragensoutput.push_back(paragensstr);

		if (paragensoutput.back().size() > linhas_max[2])
			linhas_max[2] = paragensoutput.back().size();

		temposstr.resize(0);
		for (int j = 0; j < LinhasGlobais[i].tempoviagem.size() - 1; ++j)
		{
			temposstr += to_string(LinhasGlobais[i].tempoviagem[j]) + ", ";
		}
		temposstr += to_string(LinhasGlobais[i].tempoviagem.back());
		temposoutput.push_back(temposstr);

		if (temposoutput.back().size() > linhas_max[3])
			linhas_max[3] = temposoutput.back().size();

	}

	cout << "ID" << addspaces(linhas_max[0] - 2);
	cout << " | Nome" << addspaces(linhas_max[1] - 4);
	cout << " | Paragens" << addspaces(linhas_max[2] - 8);
	cout << " | Tempo entre paragens" << addspaces(linhas_max[3] - 20);


	int table_length = 3 + 3 + 3 + linhas_max[0] + linhas_max[1] + linhas_max[2] + linhas_max[3];
	cout << "\n";

	for (int i = 0; i < table_length; ++i)
	{
		cout << "-";
	}
	cout << "\n";

	for (int i = 0; i < LinhasGlobais.size(); ++i)
	{

		cout << LinhasGlobais[i].ID << addspaces(linhas_max[0] - intsize(LinhasGlobais[i].ID));
		cout << " | " << LinhasGlobais[i].freq << addspaces(linhas_max[1] - intsize(LinhasGlobais[i].freq));
		cout << " | " << paragensoutput[i] << addspaces(linhas_max[2] - paragensoutput[i].size());
		cout << " | " << temposoutput[i] << addspaces(linhas_max[3] - temposoutput[i].size());

		cout << "\n";
	}

	cout << "\n\n9- Voltar atras\n";
	cout << "0- Encerrar programa\n";
	cout << "\n";

	string input;

	while (1)
	{
		cout << "Selecione uma opcao: ";

		getline(cin, input);
		cout << "\n";

		if (input == "9")
		{
			Menu3();
			break;
		}

		if (input == "0")
			exit(0);

		cout << "Input invalido\n";

	}


}

// Visualizacao de condutores
void Menu3para2()
{
	ClearScreen();
	PrintBanner();

	// Formatacao da tabela
	vector<int> condutores_max{ 2,4,10,13,13 };

	for (int i = 0; i < CondutoresGlobais.size(); ++i)
	{
		if (intsize(CondutoresGlobais[i].ID) > condutores_max[0])
			condutores_max[0] = intsize(CondutoresGlobais[i].ID);

		if (CondutoresGlobais[i].nome.size() > condutores_max[1])
			condutores_max[1] = CondutoresGlobais[i].nome.size();

		if (intsize(CondutoresGlobais[i].HorasTurno) > condutores_max[2])
			condutores_max[2] = intsize(CondutoresGlobais[i].HorasTurno);

		if (intsize(CondutoresGlobais[i].HorasSemanais) > condutores_max[3])
			condutores_max[3] = intsize(CondutoresGlobais[i].HorasSemanais);

		if (intsize(CondutoresGlobais[i].HorasDescanco) > condutores_max[4])
			condutores_max[4] = intsize(CondutoresGlobais[i].HorasDescanco);

	}

	cout << "ID" << addspaces(condutores_max[0] - 2);
	cout << " | Nome" << addspaces(condutores_max[1] - 4);
	cout << " | HorasTurno" << addspaces(condutores_max[2] - 10);
	cout << " | HorasSemanais" << addspaces(condutores_max[3] - 13);
	cout << " | HorasDescanco" << addspaces(condutores_max[4] - 13);


	int table_length = 3 + 3 + 3 + 3 + condutores_max[0] + condutores_max[1] + condutores_max[2] + condutores_max[3] + condutores_max[4];
	cout << "\n";

	for (int i = 0; i < table_length; ++i)
	{
		cout << "-";
	}
	cout << "\n";

	for (int i = 0; i < CondutoresGlobais.size(); ++i)
	{

		cout << CondutoresGlobais[i].ID << addspaces(condutores_max[0] - intsize(CondutoresGlobais[i].ID));
		cout << " | " << CondutoresGlobais[i].nome << addspaces(condutores_max[1] - CondutoresGlobais[i].nome.size());
		cout << " | " << CondutoresGlobais[i].HorasTurno << addspaces(condutores_max[2] - intsize(CondutoresGlobais[i].HorasTurno));
		cout << " | " << CondutoresGlobais[i].HorasSemanais << addspaces(condutores_max[3] - intsize(CondutoresGlobais[i].HorasSemanais));
		cout << " | " << CondutoresGlobais[i].HorasDescanco << addspaces(condutores_max[4] - intsize(CondutoresGlobais[i].HorasDescanco));
		cout << "\n";
	}


	cout << "\n\n9- Voltar atras\n";
	cout << "0- Encerrar programa\n";
	cout << "\n";

	string input;

	while (1)
	{
		cout << "Selecione uma opcao: ";

		getline(cin, input);
		cout << "\n";

		if (input == "9")
		{
			Menu3();
			break;
		}

		if (input == "0")
			exit(0);

		cout << "Input invalido\n";

	}

}


void Menu4()
{
	ClearScreen();
	PrintBanner();


	int linhaplace = -1, partidaplace = -1, chegadaplace = -1;
	string partida, chegada, tempstr;

	// Se nao for um numero, pedir novo input
	while (1)
	{
		cout << "\nInsira o ID da linha:";
		getline(cin, tempstr);

		// Condicao para a continuacao do programa
		if (is_numeric(tempstr))
		{

			// Verificar se ja existte alguma linha com o ID igual ao inserido
			for (int i = 0; i < LinhasGlobais.size(); ++i)
			{
				if (LinhasGlobais[i].ID == stoi(tempstr))
				{
					linhaplace = i;
					break;
				}
			}

			if (linhaplace > -1)
				break;
			else
				cout << "\nLinha nao encontrada!";
		}
		else
		{
			cout << "\nInput invalido!";
		}
	}

	cout << "\nAs paragens sao: ";
	for (int i = 0; i < LinhasGlobais[linhaplace].paragens.size() - 1; ++i)
	{
		cout << LinhasGlobais[linhaplace].paragens[i] << ", ";
	}
	cout << LinhasGlobais[linhaplace].paragens.back();
	cout << "\n";

	// Se existir algum numero na sequencia, pedir novo input
	while (1)
	{
		cout << "\nInsira a paragem de partida:";

		getline(cin, tempstr);
		erasespaces(tempstr);

		// Condicao para a continuacao do programa
		if (tempstr.size() > 1)
		{
			bool test = -1;
			//Procurar por paragem na linha
			for (int i = 0; i < LinhasGlobais[linhaplace].paragens.size(); ++i)
			{
				if (LinhasGlobais[linhaplace].paragens[i] == tempstr)
				{
					partidaplace = i;
					partida = tempstr;
					break;
				}
			}

			if (partidaplace > -1)
			{
				break;
			}
			else
				cout << "\nParagem nao encontrada!";
		}
		else
			cout << "\nInput invalido!";
	}

	cout << "\nAs paragens sao: ";
	for (int i = 0; i < LinhasGlobais[linhaplace].paragens.size() - 1; ++i)
	{
		if (i != partidaplace)
		{
			cout << LinhasGlobais[linhaplace].paragens[i];

			if (i != LinhasGlobais[linhaplace].paragens.size() - 1)
				cout << ", ";
		}

	}
	cout << "\n";

	// Se existir algum numero na sequencia, pedir novo input
	while (1)
	{
		cout << "\nInsira a paragem de chegada:";

		getline(cin, tempstr);
		erasespaces(tempstr);

		// Condicao para a continuacao do programa
		if (tempstr.size() > 1)
		{
			//Procurar por paragem na linha
			for (int i = 0; i < LinhasGlobais[linhaplace].paragens.size(); ++i)
			{
				if (LinhasGlobais[linhaplace].paragens[i] == tempstr)
				{
					chegadaplace = i;
					chegada = tempstr;
					break;
				}
			}

			if (chegada == partida)
				cout << "\nParagem de partida nao pode ser igual a paragem de chegada!";
			else
			{
				if (chegadaplace > -1)
					break;
				else
					cout << "\nParagem nao encontrada!";
			}
		}
		else
			cout << "\nInput invalido!";
	}

	int somadetempos = 0;
	if (partidaplace > chegadaplace)
		swap(partidaplace, chegadaplace);

	for (int i = partidaplace; i < chegadaplace; ++i)
	{
		somadetempos += LinhasGlobais[linhaplace].tempoviagem[i];
	}

	ClearScreen();
	PrintBanner();

	cout << "O tempo de viagem e de " << somadetempos << " minutos";
	cout << "\n\nPressione qualquer tecla para continuar...";
	cin.get();

	MainMenu();
}


int main()
{
	if (linhasfile.fail())
	{
		cout << "O ficheiro \"linhas\" nao existe!\n";
		return 0;
	}

	if (condutoresfile.fail())
	{
		cout << "O ficheiro \"condutores\" nao existe!\n";
		return 0;
	}

	LoadLinhas();
	LoadCondutores();

	MainMenu();


fim:	cout << "\n";
	return 0;
}