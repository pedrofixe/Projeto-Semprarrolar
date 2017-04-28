// 🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌
// BUS MANAGMENT INTERFACE 1.0

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
// Bibliotecas necessarias para adicionar delays 'as transicoes entre menus e ao loading screen (cross-plataform)
#include <chrono>
#include <thread>
// Pairs vao ser empregues com o objetivo de tornar a visualizacao de horarios de paragens mais eficiente
#include <utility>
// A funcao reverse() para elementos da stl é requerida uma vez
#include <algorithm>
// A funcao abs() também é util para tornar o codigo mais legivel 
#include <cmath>

#define DB_LINHAS		 "linhas"
#define DB_MOTORISTAS	 "condutores"

// Como os autocarros nao operam 24/7 é realista definir uma hora de inicio e outra de fim.
#define HORARIO_INICIO 8
#define HORARIO_FIM 22

using namespace std;

// main func possible Return Values
enum returnIndicators {
	EXIT_FAILURE_FILE_READ_ERROR = -1,
	EXIT_NO_ERROR = 0
};

// Declaração de novos tipos simples a utilizar.
typedef unsigned short tempo_t;

// Estruturas a utilizar.

struct Paragem {
	string nome;
};

struct Linha {
	string ID;
	tempo_t freq;
	vector<Paragem> paragens;
	vector<tempo_t> tempoViagem;
};

struct Motorista {
	string ID;
	string nome;
	tempo_t HorasTurno;
	tempo_t HorasPorSemana;
	tempo_t HorasDescanso;
};

vector <Motorista> Condutores;
vector <Linha> Linhas;
vector < pair<Paragem, vector<Linha*> > > ParagensCorrespondencia; // Correspondencia entre Paragens => Linhas


// Protos

void ShowLoadingScreen();
void MostrarHorariosLinha(const Linha & linha);
void displayFindLinhasDaParagem();
void MostrarLinhasQuePassamParagem(const Paragem& , const vector<Linha*>& );
void displayCalcularViagem();
void MostrarViagemEntreParagens(const string& , const string& );
void displayCalcularNrCondutoresLinha();
void ClearScreen();
void ShowAsciiLogo();
void displayMainScreen();
void displayGerirCondutoresLinhasMenu();
void displayAddCondutorMenu();
void displayMainEditCondutorMenu();
void displayEditCondutorMenu(Motorista&);
void displayRemoveCondutorMenu();
void ListarMotoristas(const string&);
void displayAddLinhaMenu();
void displayMainEditLinhasMenu();
void displayEditLinhaMenu(Linha & linha);
void displayRemoveLinhaMenu();
void ListarLinhas();
void displayTabelasHorarios();
void ImprimirHorariosLinha(const vector<Paragem>& vec_paragens, const vector <tempo_t> tempoViagem, const tempo_t freq, const tempo_t offset);
void VisHorarioParagem();
void MostrarHorariosParagem(const pair<Paragem, vector<Linha*>>&);
int IndiceElemento(const vector<Paragem>& vec_paragens, const Paragem & paragem);
int IndiceElemento(const vector<Paragem>& vec_paragens, const string & paragem);
int CalculaOffset(const vector<tempo_t> vec_tempoViagem, const unsigned int & nrParagem);
void ImprimeHorarios(const tempo_t & Inicio, const tempo_t & Fim, const tempo_t & offsetInicial, const tempo_t & frequencia);
void VisHorarioLinha();
void MostrarLinhas();
void MostrarParagens();
void SleepExecution(unsigned int);
bool loadData();
bool loadLinhas();
bool loadMotoristas();
void saveLinhas();
void saveMotoristas();
void ReconstruirCorrespondenciaParagemLinhas();
void AdicionarParagemCorrespondencia(Linha & linha, const Paragem & paragem);
void trimString(string&);
void LerParagensLinha(const string&, vector<Paragem>&);
void LerIntervalosLinha(const string&, vector<tempo_t>&);

// Código do Programa.

int main() {
	ShowLoadingScreen(); // 😃
	ClearScreen();
	if (!loadData()) {
		cerr << "Nao foi possivel abrir os ficheiros com a informacao dos motoristas e das linhas." << endl;
		return EXIT_FAILURE_FILE_READ_ERROR;
	}
	displayMainScreen();
	return EXIT_NO_ERROR;
}


// Mostrar Loading Screen Inicial

void ShowLoadingScreen() {
	cout << endl;
	ShowAsciiLogo();
	cout << endl << endl << endl << endl << endl;

	string hashes;
	for (int i = 1; i <= 100; i++) {
		cout << "\r"; // Regressar ao inicio da linha
		cout << setw(27) << "[";   // Fazer print para o centro
		string hashes;
		for (int j = 1; j <= i; j += 2) {
			hashes += "#";
		}
		cout << left << setw(50) << hashes << right;
		cout << "]";
		cout << setw(5) << i << "%";
		SleepExecution(10); // suspender execução durante 10 ms
	}
	cout << endl;
	SleepExecution(250);
	cout << setw(60) << "Loading Concluido";
	for (int i = 1; i <= 3; i++) {
		SleepExecution(150);
		cout << ".";
	}
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
}

void ShowAsciiLogo() {
	string blankFiller = "             ";
	cout << blankFiller << "  _____   ___  ___ ___  ____   ____    ____  ____   ____    ___   _       ____  ____  " << endl;
	cout << blankFiller << " / ___/  /  _]|   |   ||    \\ |    \\  /    ||    \\ |    \\  /   \\ | |     /    ||    \\ " << endl;
	cout << blankFiller << "(   \\_  /  [_ | _   _ ||  o  )|  D  )|  o  ||  D  )|  D  )|     || |    |  o  ||  D  )" << endl;
	cout << blankFiller << " \\__  ||    _]|  \\_/  ||   _/ |    / |     ||    / |    / |  O  || |___ |     ||    / " << endl;
	cout << blankFiller << " /  \\ ||   [_ |   |   ||  |   |    \\ |  _  ||    \\ |    \\ |     ||     ||  _  ||    \\ " << endl;
	cout << blankFiller << " \\    ||     ||   |   ||  |   |  .  \\|  |  ||  .  \\|  .  \\|     ||     ||  |  ||  .  \\" << endl;
	cout << blankFiller << "  \\___||_____||___|___||__|   |__|\\_||__|__||__|\\_||__|\\_| \\___/ |_____||__|__||__|\\_|" << endl;
	cout << blankFiller << "                                                                                      " << endl;

}

void displayMainScreen() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl << endl;
	cout << "---- Bem-Vindo utilizador! Por favor selecione uma opcao: " << endl << endl;
	cout << setw(5) << "" << "1. Gestao de Linhas e Condutores" << endl << endl;
	cout << setw(5) << "" << "2. Visualizar horarios de linhas ou de paragens." << endl << endl;
	cout << setw(5) << "" << "3. Procurar linhas que incluem dada paragem." << endl << endl;
	cout << setw(5) << "" << "4. Calcular viagem entre 2 paragens." << endl << endl;
	cout << setw(5) << "" << "5. Calcular quantos condutores sao precisos para dada linha." << endl << endl;
	cout << setw(5) << "" << "S. Sair" << endl << endl << endl;
	char opcao;
	cout << "Opcao: "; cin >> opcao;
	cin.clear();
	cin.ignore(50,'\n');
	switch (opcao){
		case '1':
		ClearScreen();
		SleepExecution(400);
		displayGerirCondutoresLinhasMenu();
		break;
		case '2':
		ClearScreen();
		SleepExecution(400);
		displayTabelasHorarios();
		break;
		case '3':
		ClearScreen();
		SleepExecution(400);
		displayFindLinhasDaParagem();
		break;
		case '4':
		ClearScreen();
		SleepExecution(400);
		displayCalcularViagem();
		break;
		case '5':
		ClearScreen();
		SleepExecution(400);
		displayCalcularNrCondutoresLinha();
		break;
		case 'S': case 's':
		SleepExecution(800);
		return;
		default:
		cout << "Nao inseriste uma opcao valida...";
		SleepExecution(1500);
		ClearScreen();
		displayMainScreen();
		break;
	}
}

void displayGerirCondutoresLinhasMenu() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << "---- Menu de Gestao de linhas e condutores. Por favor selecione uma opcao: " << endl << endl << endl;
	cout << setw(5) << "" << "1. Adicionar Condutor" << endl << endl;
	cout << setw(5) << "" << "2. Modificar Condutor." << endl << endl;
	cout << setw(5) << "" << "3. Remover Condutor." << endl << endl;
	cout << setw(5) << "" << "4. Adicionar Linha." << endl << endl;
	cout << setw(5) << "" << "5. Modificar Linha." << endl << endl;
	cout << setw(5) << "" << "6. Remover Linha" << endl << endl;
	cout << setw(5) << "" << "V. Voltar ao menu inicial" << endl << endl;
	char opcao;
	cout << "Opcao: "; cin >> opcao;
	switch (opcao) {
		case '1':
		SleepExecution(200);
		ClearScreen();
		displayAddCondutorMenu();
		break;
		case '2':
		SleepExecution(200);
		ClearScreen();
		displayMainEditCondutorMenu();
		break;
		case '3':
		SleepExecution(200);
		ClearScreen();
		displayRemoveCondutorMenu();
		break;
		case '4':
		SleepExecution(200);
		ClearScreen();
		displayAddLinhaMenu();
		break;
		case '5':
		SleepExecution(200);
		ClearScreen();
		displayMainEditLinhasMenu();
		break;
		case '6':
		SleepExecution(200);
		ClearScreen();
		displayRemoveLinhaMenu();
		break;
		case 'V': case 'v':
		SleepExecution(200);
		ClearScreen();
		displayMainScreen();
		break;
		default:
		cout << "Nao inseriste uma opcao valida!" << endl;
		SleepExecution(2000);
		ClearScreen();
		displayGerirCondutoresLinhasMenu();
		break;
	}
}

void displayAddCondutorMenu() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << setw(10) << "" << "Painel de adicao de condutores. Por favor segue as instrucoes:" << endl << endl;

	Motorista motoristaNovo;
	string temp;

	cout << "Identificador do Motorista: "; cin >> motoristaNovo.ID;

	cin.ignore(10, '\n');

	cout << "Nome do Motorista: "; getline(cin, motoristaNovo.nome);
	cin.ignore(10000, '\n');
	cin.clear();
	cout << "Horas p/Turno: "; cin >> motoristaNovo.HorasTurno;
	cout << "Carga semanal (em horas): "; cin >> motoristaNovo.HorasPorSemana;
	cout << "Horas de descanso (entre turnos): "; cin >> motoristaNovo.HorasDescanso;
	cout << endl << setw(5) << "" << "Motorista adicionado com sucesso!" << endl;

	Condutores.push_back(motoristaNovo);
	saveMotoristas();

	SleepExecution(2000);
	displayGerirCondutoresLinhasMenu();

}

void displayMainEditCondutorMenu() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << setw(5) << "" << "Painel de edicao de condutores. Por favor insere o identificador do condutor que desejas editar." << endl << endl;

	ListarMotoristas(""); // listar todos os motoristas

	cout << endl;
	string identificador;
	cout << "Identificador: "; cin >> identificador;
	SleepExecution(500);
	// Vamos verificar se esse identificador é valido...
	for (Motorista &condutor : Condutores) { // o qualificativo const não pode ser usado aqui porque o elemento deve ser mutavel para poder ser passado a funcao de editar o condutor
		if (condutor.ID == identificador) {
			ClearScreen();
			displayEditCondutorMenu(condutor);
			return;
		}
	}
	// Identificador nao valido..
	cout << "Esse Identificador nao e valido...";
	SleepExecution(1500);
	ClearScreen();
	displayGerirCondutoresLinhasMenu();
}

void displayEditCondutorMenu(Motorista &condutor) {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	ListarMotoristas(condutor.ID);
	cout << endl;
	cout << setw(2) << "Insere os novos dados. Se desejas nao editar algum atributo insere 0." << endl << endl;

	string stemp;
	tempo_t ttemp;

	cin.ignore(10, '\n');

	cout << setw(5) << "Identificador do Motorista: "; getline(cin, stemp);
	if (stemp != "0")	condutor.ID = stemp;
	cout << setw(5) << "Nome do Motorista: "; getline(cin, stemp);
	if (stemp != "0")	condutor.nome = stemp;
	cout << setw(5) << "Horas p/Turno: "; cin >> ttemp;
	if (ttemp != 0)	condutor.HorasTurno = ttemp;
	cout << setw(5) << "Carga semanal (em horas): "; cin >> ttemp;
	if (ttemp != 0)	condutor.HorasPorSemana = ttemp;
	cout << setw(5) << "Horas de descanso (entre turnos): "; cin >> ttemp;
	if (ttemp != 0)	condutor.HorasPorSemana = ttemp;

	cout << endl << setw(2) << "Condutor editado com sucesso." << endl;
	saveMotoristas();
	SleepExecution(1000);
	ClearScreen();
	displayGerirCondutoresLinhasMenu();



}

void displayRemoveCondutorMenu() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << setw(5) << "" << "Painel de eliminacao de condutores. Por favor insere o identificador do condutor que desejas remover." << endl << endl;

	ListarMotoristas(""); // listar todos os motoristas

	cout << endl;
	string identificador;
	cout << "Identificador: "; cin >> identificador;
	SleepExecution(500);
	// Vamos verificar se esse identificador é valido...
	bool valido = false;
	for (size_t i = 0; i < Condutores.size(); i++) {
		if (Condutores[i].ID == identificador) {
			// remover condutor..
			Condutores.erase(Condutores.begin() + i); // alguma bruxaria aqui para o meio mas pronto. Condutores.begin() retorna um iterador para o inicio do vetor. Quando lhe somamos i obtemos um iterador para o elemento que queremos eliminar
			valido = true;
			break;
		}
	}
	// Identificador nao valido..
	if(!valido) cout << "Esse Identificador nao e valido...";
	else cout << "Condutor eliminado com sucesso.";
	saveMotoristas();
	SleepExecution(1500);
	ClearScreen();
	displayGerirCondutoresLinhasMenu();
}

void ListarMotoristas(const string &identificador = "") { // se o primeiro argumento for a string vazia entao esta funcao imprime uma lisa formatada de todos os condutores
	cout << setw(2) << "" << setw(15) << left << "Identificador" << setw(30) << "Nome" << setw(25) << "Horas p/ Turno" << setw(25) << "Carga Semanal (horas)" << setw(20) << "Horas de descanso" << endl;
	for (const Motorista &condutor : Condutores) { // sintaxe introduzida pelo standard c++11
		if (identificador != "" && condutor.ID != identificador) continue;
		cout << setw(2) << "" << setw(15) << condutor.ID << setw(30) << condutor.nome << setw(25) << condutor.HorasTurno << setw(25) << condutor.HorasPorSemana << setw(20) << condutor.HorasDescanso << endl;
	}
	cout << right;
}

void displayAddLinhaMenu() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << setw(10) << "" << "Painel de adicao de linhas. Por favor segue as instrucoes:" << endl << endl;

	Linha linhaNova;
	string temp;

	cin.ignore(10, '\n');

	cout << "Identificador da Linha: "; getline(cin, linhaNova.ID);
	cout << "Frequencia (minutos): "; cin >> linhaNova.freq;
	cin.ignore(10000, '\n');
	cin.clear();

	cout << "Insere agora a lista de paragens (faz enter apos inserires cada paragem e pressiona CTRL Z para parar): ";

	while (getline(cin, temp)) {
		Paragem paragemNova;
		paragemNova.nome = temp;
		linhaNova.paragens.push_back(paragemNova);
	}

	cin.ignore(10, '\n');
	cin.clear();

	cout << "Perfeito! Insere agora o tempo de viagem entre cada paragem do percurso." << endl;

	for (size_t i = 0; i < linhaNova.paragens.size() - 1; i++) {
		tempo_t tempo;
		cout << "Tempo de viagem entre " << linhaNova.paragens[i].nome << " e " << linhaNova.paragens[i + 1].nome << "?";
		cin >> tempo;
		linhaNova.tempoViagem.push_back(tempo);
	}
	
	Linhas.push_back(linhaNova);

	cout << endl << setw(5) << "" << "Linha adicionada com sucesso!" << endl;
	ReconstruirCorrespondenciaParagemLinhas();
	saveLinhas();
	SleepExecution(2000);
	displayGerirCondutoresLinhasMenu();
}

void displayMainEditLinhasMenu() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << setw(5) << "" << "Painel de edicao de Linhas. Por favor insere o identificador da linha que desejas editar." << endl << endl;

	ListarLinhas();

	cout << endl;
	string identificador;
	cout << "Identificador: "; cin >> identificador;
	SleepExecution(500);
	// Vamos verificar se esse identificador é valido...
	for (Linha &linha : Linhas) { // o qualificativo const não pode ser usado aqui porque o elemento deve ser mutavel para poder ser passado a funcao de editar o condutor
		if (linha.ID == identificador) {
			ClearScreen();
			displayEditLinhaMenu(linha);
			return;
		}
	}
	// Identificador nao valido..
	cout << "Esse Identificador nao e valido...";
	SleepExecution(1500);
	ClearScreen();
	displayGerirCondutoresLinhasMenu();
}


void displayEditLinhaMenu(Linha &linha) {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	
	cout << setw(2) << "" << "Identificador atual: " << linha.ID << endl;
	cout << setw(2) << "" << "Frequencia da linha atual: " << linha.freq << endl;
	cout << setw(2) << "" << "Paragens e tempo de viagem entre elas: " << endl;

	cout << setw(1) << "";
	for (size_t i = 0; i < linha.paragens.size(); i++) {
		if (i == linha.paragens.size() - 1) {
			cout << linha.paragens[i].nome << endl << endl;;
		}
		else cout << linha.paragens[i].nome << " --" << linha.tempoViagem[i] << "--> ";
	}

	cout << endl << endl;
	cout << setw(2) << "Insere os novos dados. Se desejas nao editar algum atributo insere 0." << endl << endl;

	string stemp;
	tempo_t ttemp;

	cin.ignore(10, '\n');
	cin.clear();

	cout << "Novo identificador: "; getline(cin, stemp);
	if (stemp != "0") linha.ID = stemp;
	cout << "Nova frequencia: "; cin >> ttemp;
	if (ttemp != 0) linha.freq = ttemp;

	cout << "Mudar paragens? (S/N)"; cin >> stemp;

	if (stemp == "s" || stemp == "S") {
		linha.paragens.clear();
		linha.tempoViagem.clear();
		cout << linha.paragens.size();
		cout << "Insere agora a lista de paragens (faz enter apos inserires cada paragem e pressiona CTRL Z para parar): ";

		cin.ignore(10, '\n');
		cin.clear();

		while (getline(cin, stemp)) {
			Paragem paragemNova;
			paragemNova.nome = stemp;
			linha.paragens.push_back(paragemNova);
		}

		cin.ignore(10, '\n');
		cin.clear();

		cout << "Perfeito! Insere agora o tempo de viagem entre cada paragem do percurso." << endl;

		for (size_t i = 0; i < linha.paragens.size() - 1; i++) {
			cout << "Tempo de viagem entre " << linha.paragens[i].nome << " e " << linha.paragens[i + 1].nome << "?";
			cin >> ttemp;
			linha.tempoViagem.push_back(ttemp);
		}
	}

	cin.ignore(10, '\n');

	cout << endl << setw(2) << "Linha Editada com sucesso." << endl;
	ReconstruirCorrespondenciaParagemLinhas();
	saveLinhas();
	SleepExecution(1000);
	ClearScreen();
	displayGerirCondutoresLinhasMenu();
}

void displayRemoveLinhaMenu() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << setw(5) << "" << "Painel de eliminacao de Linhas. Por favor insere o identificador da linha que desejas remover." << endl << endl;

	ListarLinhas(); // listar todos os motoristas

	cout << endl;
	string identificador;
	cout << "Identificador: "; cin >> identificador;
	SleepExecution(500);
	// Vamos verificar se esse identificador é valido...
	bool valido = false;
	for (size_t i = 0; i < Linhas.size(); i++) {
		if (Linhas[i].ID == identificador) {
			// remover linha..
			Linhas.erase(Linhas.begin() + i); // Linhas.begin() retorna um iterador para o inicio do vetor. Quando lhe somamos i obtemos um iterador para o elemento que queremos eliminar
			valido = true;
			break;
		}
	}
	// Identificador nao valido..
	if (!valido) cout << "Esse Identificador nao e valido...";
	else cout << "Linha Eliminada com sucesso.";
	ReconstruirCorrespondenciaParagemLinhas();
	saveLinhas();
	SleepExecution(1500);
	ClearScreen();
	displayGerirCondutoresLinhasMenu();
}

void ListarLinhas() {
	cout << setw(2) << "" << setw(15) << left << "Identificador" << setw(20) << "Numero de Paragens" << endl;
	for (const Linha &linha : Linhas) { // sintaxe introduzida pelo standard c++11
		cout << setw(2) << "" << setw(15) << linha.ID << setw(20) << linha.paragens.size() << endl;
	}
	cout << right;
}


void displayTabelasHorarios() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << "---- Menu de Visualizacao de horarios de linhas e de paragens. Por favor selecione uma opcao: " << endl << endl << endl;
	cout << setw(5) << "" << "1. Visualizar horario de uma paragem." << endl << endl;
	cout << setw(5) << "" << "2. Visualizar horario de uma linha." << endl << endl;
	cout << setw(5) << "" << "V. Voltar ao menu inicial" << endl << endl;

	char opcao;
	cout << "Opcao: "; cin >> opcao;
	switch (opcao) {
		case '1':
		SleepExecution(200);
		ClearScreen();
		VisHorarioParagem();
		break;
		case '2':
		SleepExecution(200);
		ClearScreen();
		VisHorarioLinha();
		break;
		case 'V': case 'v':
		SleepExecution(200);
		ClearScreen();
		displayMainScreen();
		break;
		default:
		cout << "Nao inseriste uma opcao valida!" << endl;
		SleepExecution(2000);
		ClearScreen();
		displayTabelasHorarios();
		break;
	}

}

void VisHorarioParagem() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << "---- Menu de Visualizacao de horarios de paragens. Por favor selecione uma paragem de entre as seguintes: " << endl << endl;

	MostrarParagens();

	cout << endl << endl;

	string opcao;
	cout << "Paragem: ";

	cin.ignore(10, '\n');
	cin.clear();

	getline(cin, opcao);

	trimString(opcao);
	
	// Processar opcao
	for (const auto &par : ParagensCorrespondencia) {
		if (par.first.nome == opcao) {
			SleepExecution(500);
			ClearScreen();
			MostrarHorariosParagem(par);
			return;
		}
	}
	cout << setw(5) << "" << "Paragem nao encontrada!";
	SleepExecution(1500);
	ClearScreen();
	displayTabelasHorarios();
}

void MostrarHorariosParagem(const pair < Paragem, vector <Linha*> > &par) {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;

	cout << setw(10) << "" << "A mostrar horarios da paragem " << par.first.nome << ":" << endl << endl;
	for (Linha* linha : par.second) { // Iterar sobre cada linha que passa na paragem.
		const tempo_t frequencia = linha->freq; // frequencia da linha
		//Calcular tempo entre a primeira paragem e a paragem que queremos obter os horarios
		const unsigned int numeroDaParagem = IndiceElemento(linha->paragens, par.first);
		const tempo_t offsetHorarios = CalculaOffset(linha->tempoViagem, numeroDaParagem);

		// Mostrar no sentido de ida
		if (par.first.nome != linha->paragens[linha->paragens.size() - 1].nome) {
			cout << setw(5) << "Horario da linha " << linha->ID << " no sentido " << linha->paragens[0].nome << " -> " << linha->paragens[linha->paragens.size() - 1].nome << " :" << endl;
			ImprimeHorarios(HORARIO_INICIO, HORARIO_FIM, offsetHorarios, frequencia);
		}

		if (par.first.nome != linha->paragens[0].nome) {
			cout << endl << endl;
			// Mostrar no sentido de volta
			const tempo_t tempoViagemTotal = CalculaOffset(linha->tempoViagem, linha->paragens.size() - 1);
			cout << setw(5) << "Horario da linha " << linha->ID << " no sentido " << linha->paragens[linha->paragens.size() - 1].nome << " -> " << linha->paragens[0].nome << " :" << endl;
			ImprimeHorarios(HORARIO_INICIO, HORARIO_FIM, tempoViagemTotal + (tempoViagemTotal - offsetHorarios), frequencia);
		}

		cout << endl << endl << "Pressione enter para continuar";
		getchar();
		ClearScreen();
		displayTabelasHorarios();
	}
}

int IndiceElemento(const vector<Paragem> &vec_paragens, const Paragem &paragem) {
	for (size_t i = 0; i < vec_paragens.size(); i++) {
		if (vec_paragens[i].nome == paragem.nome) {
			return i;
		}
	}
	return -1; // vamos esperar que isto nao aconteça...
}

//Funcao overloaded. Util quando for necessario invoca-la pelo nome direto da paragem sem a struct envolvente
int IndiceElemento(const vector<Paragem> &vec_paragens, const string &paragem) {
	for (size_t i = 0; i < vec_paragens.size(); i++) {
		if (vec_paragens[i].nome == paragem) {
			return i;
		}
	}
	return -1; // vamos esperar que isto nao aconteça...
}

int CalculaOffset(const vector<tempo_t> vec_tempoViagem, const unsigned int &nrParagem) {
	unsigned int acumulador = 0;
	for (unsigned int i = 0; i < nrParagem; i++) {
		acumulador += vec_tempoViagem[i];
	}
	return acumulador;
}

void ImprimeHorarios(const tempo_t &Inicio, const tempo_t &Fim, const tempo_t &offsetInicial, const tempo_t &frequencia) {
	tempo_t horas = Inicio, minutos = 0;
	while (true) {
		if (minutos >= 60) {
			horas+= minutos/60;
			minutos %= 60;
			if (Fim <= horas)
				return;
		}

		tempo_t horasLoop = horas;
		tempo_t minutosLoop = minutos + offsetInicial;
		if (minutosLoop >= 60) horasLoop += minutosLoop/60;
		minutosLoop %= 60;
		cout << horasLoop << ":";
		if (minutosLoop < 10) cout << "0";
		cout << minutosLoop << " ";
		minutos += frequencia;
	}
}


// Imprime lista de paragens
void MostrarParagens() {
	bool firstIteration = true;
	for (const auto &elem : ParagensCorrespondencia) {
		if (firstIteration) {
			(firstIteration = false);
		}
		else (cout << ",");
		cout << " " << elem.first.nome;
	}
}


void VisHorarioLinha() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << "---- Menu de Visualizacao de horarios de Linhas. Por favor selecione uma Linha de entre as seguintes: " << endl << endl;

	MostrarLinhas();

	cout << endl << endl;

	string opcao;
	cout << "Linha: ";

	cin.ignore(10, '\n');
	cin.clear();

	getline(cin, opcao);

	trimString(opcao);

	// Processar opcao
	for (const Linha &linha : Linhas) {
		if (linha.ID == opcao) {
			ClearScreen();
			SleepExecution(500);
			MostrarHorariosLinha(linha);
			return;
		}
	}

	cout << setw(5) << "" << "Linha nao encontrada!";
	SleepExecution(1500);
	ClearScreen();
	displayTabelasHorarios();
}

void MostrarLinhas() { // imprime lista de linhas
	bool firstIteration = true;
	for (const Linha &linha : Linhas) {
		if (firstIteration) {
			(firstIteration = false);
		}
		else (cout << ",");
		cout << " " << linha.ID;
	}
}

void MostrarHorariosLinha(const Linha& linha) {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << setw(10) << "" << "A mostrar horarios da linha " << linha.ID << ":" << endl << endl << endl;

	//Imprimir horarios IDA
	cout << setw(5) << "" << "Sentido " << linha.paragens[0].nome << " -> " << linha.paragens[linha.paragens.size() - 1].nome << " :" << endl << endl;
	ImprimirHorariosLinha(linha.paragens, linha.tempoViagem, linha.freq, 0);
	cout << endl << endl;

	//Imprimir horarios VOLTA
	vector<Paragem> vec_paragens = linha.paragens;
	vector<tempo_t> vec_tempoViagem = linha.tempoViagem;

	// // Calcular o offset inicial, isto é, o tempo que o primeiro autocarro do dia demora a fazer o percurso de ida
	const unsigned int offset = abs(CalculaOffset(vec_tempoViagem, vec_paragens.size()-1 ) );

	reverse(vec_paragens.begin(), vec_paragens.end()); // Alterar a ordem do vetor para o inverso para imprimir o horario de VOLTA
	reverse(vec_tempoViagem.begin(), vec_tempoViagem.end()); // ""
	cout << setw(5) << "" << "Sentido " << linha.paragens[linha.paragens.size() - 1 ].nome << " -> " << linha.paragens[0].nome << " :" << endl << endl;
	ImprimirHorariosLinha(vec_paragens, vec_tempoViagem, linha.freq, offset);

	cout << endl << endl;
	cout << endl << "Pressione enter para continuar";
	getchar();
	ClearScreen();
	displayTabelasHorarios();

}

void ImprimirHorariosLinha(const vector<Paragem>& vec_paragens, const vector <tempo_t> tempoViagem, const tempo_t freq, const tempo_t offset = 0) {

	vector<unsigned int> widthColunas;
	//Obter largura de cada coluna & fazer header da tabela
	for (const Paragem& paragem : vec_paragens) {
		widthColunas.push_back(paragem.nome.length() + 1);
		cout << setw(paragem.nome.length() + 4) << paragem.nome;
	}
	cout << endl;
	tempo_t horasTurno = HORARIO_INICIO, minutosTurno = offset;
	while (horasTurno < HORARIO_FIM) {
		tempo_t horasLinha = horasTurno, minutosLinha = minutosTurno;
		for (size_t i = 0; i < vec_paragens.size(); i++) {
			cout << setw(widthColunas[i]) << horasLinha << ":";
			if (minutosLinha < 10)	cout << "0";
			cout << minutosLinha;

			if (!(i == vec_paragens.size() - 1)) {  //isto 'e, se a iteracao ainda nao chegou 'a ultima paragem
				minutosLinha += tempoViagem[i];
			if (minutosLinha >= 60) {
				horasLinha += minutosLinha / 60;
				minutosLinha %= 60;
			}
		}
	}

	minutosTurno += freq;
	if (minutosTurno >= 60) {
		horasTurno += minutosTurno / 60;
		minutosTurno %= 60;
	}
	SleepExecution(20);
	cout << endl;
}
}

void displayFindLinhasDaParagem() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << setw(10) << "" << "Por favor insira uma das seguintes paragens para ver quais as linhas que passam nela." << endl << endl;
	cout << " ";
	MostrarParagens();
	cout << endl << endl;
	cout << "Paragem: ";

	string opcao;

	getline(cin, opcao);

	trimString(opcao);

	// Processar opcao
	for (const auto &par : ParagensCorrespondencia) {
		if (par.first.nome == opcao) {
			SleepExecution(500);
			ClearScreen();
			MostrarLinhasQuePassamParagem(par.first, par.second);
			return;
		}
	}
	cout << setw(5) << "" << "Paragem nao encontrada!";
	SleepExecution(1500);
	ClearScreen();
	displayMainScreen();
}

void MostrarLinhasQuePassamParagem(const Paragem &paragem,const vector<Linha *> &vec_linhas) {

	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << setw(10) << "" << "Linhas que passam na paragem " << paragem.nome << ":" << endl;

	bool firstIteration = true;
	for (Linha* linha : vec_linhas) {
		if (firstIteration) {
			cout << linha->ID;
			firstIteration = false;
			continue;
		}
		cout << ", " << linha->ID;
	}

	cout << endl << endl;
	cout << "Prima enter para prosseguir." << endl;

	getchar();
	ClearScreen();
	displayMainScreen();
}

void displayCalcularViagem() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << setw(10) << "" << "Por favor insira duas paragens de modo a calcular os possiveis trajetos diretos entre as duas." << endl << endl;
	cout << " ";
	MostrarParagens();
	cout << endl << endl;

	cout << "Paragem 1: ";
	string opcao1;
	getline(cin, opcao1);
	trimString(opcao1);

	cout << "Paragem 2: ";
	string opcao2;
	getline(cin, opcao2);
	trimString(opcao2);

	cout << endl << endl;

	// Processar Selecao
	MostrarViagemEntreParagens(opcao1, opcao2);

	cout << "Prima enter para prosseguir." << endl;
	getchar();
	ClearScreen();
	displayMainScreen();
}

void MostrarViagemEntreParagens(const string &paragem1, const string &paragem2) {
	vector<Linha*> *linhas_paragem1 = nullptr, *linhas_paragem2 = nullptr;
	for (auto &par : ParagensCorrespondencia) {
		if (par.first.nome == paragem1) {
			linhas_paragem1 = &par.second;
		}
		else if (par.first.nome == paragem2) {
			linhas_paragem2 = &par.second;
		}
	}

	bool paragensValidas = true;
	if (linhas_paragem1 == nullptr) { // A paragem 1 nao existe
		cout << "A paragem 1 nao e' valida!" << endl;
		paragensValidas = false;
	}
	if (linhas_paragem2 == nullptr) { // A paragem 2 nao existe
		cout << "A paragem 2 nao e' valida!" << endl;
		paragensValidas = false;
	}
	if (!paragensValidas) {
		SleepExecution(1500);
		return;
	}

	// Encontrar intersecao das linhas que passam em ambas as paragens
	vector <Linha*> intersecao;
	for (Linha* linha_paragem1 : *linhas_paragem1) {
		for (Linha* linha_paragem2 : *linhas_paragem2) {
			if (linha_paragem1 == linha_paragem2) // podemos comparar diretamente os enderecos para ser mais eficiente
			{
				intersecao.push_back(linha_paragem1);
			}
		}
	}

	if (intersecao.empty())  // Nao ha nenhuma linha que passe em ambas as paragens
	{
		cout << "Nao ha nenhuma linha que passe em ambas as paragens!" << endl;
		return;
	}

	// Processar & Mostrar trajetos possiveis 
	unsigned int i = 0;
	for (Linha* pLinha : intersecao) {

		cout << "-----> Trajeto 1" << endl;
		cout << "--> Linha " << pLinha->ID << endl;

		// Calcular tempo de viagem
		cout << "--> Tempo de Viagem: ";
		const unsigned int numeroDaParagem1 = IndiceElemento(pLinha->paragens, paragem1);
		const unsigned int numeroDaParagem2 = IndiceElemento(pLinha->paragens, paragem2);
		const unsigned int tempoDeViagem = abs(CalculaOffset(pLinha->tempoViagem, numeroDaParagem1) - CalculaOffset(pLinha->tempoViagem, numeroDaParagem2));
		cout << tempoDeViagem << endl;
		// Apresentar percurso
		cout << "--> Percurso: ";
		if (numeroDaParagem1 < numeroDaParagem2) { // sentido de ida
			for (size_t i = numeroDaParagem1; i <= numeroDaParagem2; i++) {
				cout << pLinha->paragens[i].nome;
				if (i != numeroDaParagem2) cout << " -> ";
			}
		}
		else {
			for (size_t i = numeroDaParagem1; i >= numeroDaParagem2 && i <= numeroDaParagem1; i--) {	// O uso do tipo int nesta linha face ao size_t é com o intuito de prevenir casos de overflow que surgiram durante o teste do programa
				cout << pLinha->paragens[i].nome;
				if (i != numeroDaParagem2) cout << " -> ";
			}
		}
		cout << endl << endl;
		i++;
	}
}

void displayCalcularNrCondutoresLinha() {
	ShowAsciiLogo();
	cout << endl << endl << endl << endl;
	cout << "---- Menu de Calculo do Numero de Condutores necessarios para uma Linha. Por favor insira o numero de horas de um turno dos motoristas: " << endl << endl;
	cout << "Horas P/Turno: ";
	tempo_t NrHoras; cin >> NrHoras;

	cout << endl << "Por favor selecione uma Linha de entre as seguintes: " << endl << endl;
	MostrarLinhas();

	cout << endl << endl;

	string opcao;
	cout << "Linha: ";

	cin.ignore(10, '\n');
	cin.clear();

	getline(cin, opcao);

	trimString(opcao);

	bool linhaEncontrada = false;
	// Processar opcao
	for (const Linha &linha : Linhas) {
		if (linha.ID == opcao) {
			SleepExecution(500);
			linhaEncontrada = true;
			// --> Calcular Nr De condutores Necessarios
			// Primeiro é necessário calcular quanto tempo leva uma viagem completa da primeira paragem até à ultima
			const tempo_t tempoViagemTotal = CalculaOffset(linha.tempoViagem, linha.paragens.size() - 1);
			const unsigned int NrAutocarrosEmCirculacao = ceil((float)tempoViagemTotal / linha.freq) * 2;
			const unsigned int NrMotoristasTotal = NrAutocarrosEmCirculacao * ceil( (HORARIO_FIM - HORARIO_INICIO) / (float) NrHoras );

			cout << setw(5) << "" << "Idealmente sao necessarios " << NrMotoristasTotal << " condutores para manter a linha operacional.";

			break;
		}
	}

	if(!linhaEncontrada) cout << endl << setw(5) << "" << "Linha nao encontrada!";
	


	cout << endl << endl << "Pressione enter para continuar";
	getchar();
	ClearScreen();
	displayMainScreen();
}

// "Limpa" o ecran. todo o conteudo que estava a ser mostrado 'e empurrado para cima e deixa de ser visivel
void ClearScreen() {
	for (int i = 1; i <= 35; i++)	cout << endl;
}

// Le dados dos motoristas e das linhas
bool loadData() {
	return(loadLinhas() && loadMotoristas());
}

bool loadLinhas() {
	ifstream h_linhas(DB_LINHAS);
	if (h_linhas.fail()) {
		h_linhas.close();
		return false;
	}

	// LER LINHAS
	string linha_string;
	while (getline(h_linhas, linha_string)) {
		// LER LINHA DO FICHEIRO
		istringstream linha_stream(linha_string);
		Linha linha_estrutura;
		string Temp;
		// Ler identificador da linha
		getline(linha_stream, Temp, ';');
		trimString(Temp);
		linha_estrutura.ID = Temp;
		// Ler frequencia
		getline(linha_stream, Temp, ';');
		trimString(Temp);
		linha_estrutura.freq = (tempo_t)stoi(Temp);
		// Ler Paragens
		getline(linha_stream, Temp, ';');
		LerParagensLinha(Temp, linha_estrutura.paragens);
		// Ler Intervalos
		getline(linha_stream, Temp, '\n');
		LerIntervalosLinha(Temp, linha_estrutura.tempoViagem);

		Linhas.push_back(linha_estrutura); // adicionar ao vetor de Linhas
	}

	ReconstruirCorrespondenciaParagemLinhas();

	h_linhas.close();
	return true;
}


void LerParagensLinha(const string& frase, vector<Paragem> &vetorLinhas) {
	istringstream ssfrase(frase);
	string Temp;
	while (getline(ssfrase, Temp, ',')) {
		trimString(Temp);
		Paragem nova_paragem;
		nova_paragem.nome = Temp;
		vetorLinhas.push_back(nova_paragem);
	}
}

void LerIntervalosLinha(const string& frase, vector<tempo_t>& vetorIntervalos) {
	istringstream ssfrase(frase);
	string Temp;
	while (getline(ssfrase, Temp, ',')) {
		trimString(Temp);
		tempo_t intervalo = stoi(Temp);
		vetorIntervalos.push_back(intervalo);
	}
}

bool loadMotoristas() {
	ifstream h_motoristas(DB_MOTORISTAS);
	if (h_motoristas.fail()) {
		h_motoristas.close();
		return false;
	}

	// LER LINHAS
	string motorista_string;
	while (getline(h_motoristas, motorista_string)) {
		// LER LINHA DO FICHEIRO
		istringstream linha_stream(motorista_string);
		Motorista motorista_estrutura;
		string Temp;
		// Ler identificador do motorista
		getline(linha_stream, Temp, ';');
		trimString(Temp);
		motorista_estrutura.ID = Temp;
		// Ler Nome do motorista
		getline(linha_stream, Temp, ';');
		trimString(Temp);
		motorista_estrutura.nome = Temp;
		// Ler numero de horas consecutivas que o motorista pode trabalhar (turno)
		getline(linha_stream, Temp, ';');
		trimString(Temp);
		motorista_estrutura.HorasTurno = (tempo_t)stoi(Temp);
		// Ler numero de horas que o motorista pode trabalhar por semana
		getline(linha_stream, Temp, ';');
		trimString(Temp);
		motorista_estrutura.HorasPorSemana = (tempo_t)stoi(Temp);
		// Ler numero de horas de descanso obrigatorio apos turno
		getline(linha_stream, Temp, '\n');
		trimString(Temp);
		motorista_estrutura.HorasDescanso = (tempo_t)stoi(Temp);

		Condutores.push_back(motorista_estrutura); // adicionar ao vetor de condutores
	}
	h_motoristas.close();
	return true;
}

void saveLinhas() {
	ofstream h_linhas(DB_LINHAS);
	for (const Linha &linha : Linhas) {
		h_linhas << linha.ID << " ; " << linha.freq << " ; ";
		for (size_t i = 0; i < linha.paragens.size(); i++) {
			if (i == linha.paragens.size() - 1) {
				h_linhas << linha.paragens[i].nome << ";";
			}
			else {
				h_linhas << linha.paragens[i].nome << " , ";
			}
		}
		for (size_t i = 0; i < linha.tempoViagem.size(); i++) {
			if (i == linha.tempoViagem.size() - 1) {
				h_linhas << " " << linha.tempoViagem[i];
			}
			else {
				h_linhas << " " << linha.tempoViagem[i] << ",";
			}
		}
		h_linhas << endl;
	}
	h_linhas.close();
}


void saveMotoristas() {
	ofstream h_motoristas(DB_MOTORISTAS);
	for (const Motorista &condutor : Condutores) {
		h_motoristas << condutor.ID << " ; " << condutor.nome << " ; " << condutor.HorasTurno << " ; " << condutor.HorasPorSemana << " ; " << condutor.HorasDescanso << endl;
	}
	h_motoristas.close();
}

void ReconstruirCorrespondenciaParagemLinhas() {
	ParagensCorrespondencia.clear();
	for (Linha& linha : Linhas) {
		for (const Paragem& paragem : linha.paragens) {
			AdicionarParagemCorrespondencia(linha, paragem);
		}
	}
}

// Adicionar/Atualizar Vetor que tem a correspondencia entre Paragens -> Linhas
void AdicionarParagemCorrespondencia(Linha &linha, const Paragem &paragem){
	bool encontrado = false;
	for (auto &elemento : ParagensCorrespondencia) {
		if (elemento.first.nome == paragem.nome) {
			encontrado = true;
			elemento.second.push_back(&linha);
			break;
		}
	}
	if (!encontrado) {
		vector <Linha *> vecNovo = { &linha };
		pair<Paragem, vector<Linha*>> novoPar(paragem, vecNovo);
		ParagensCorrespondencia.push_back(novoPar);
	}
}

// Elimina espaços no inicio e no fim da string passada como argumento
void trimString(string& frase) {
	while (frase.find_first_of(' ') == 0) { // eliminar espacos do inicio
		frase.erase(0, 1);
	}
	while (frase.find_last_of(' ') == (frase.length() - 1)) { // eliminar espaços do final
		frase.erase(frase.find_last_of(' '));
	}
}

// Suspende a execucacao do programa durante x milisegundos
void SleepExecution(unsigned int x) {
	this_thread::sleep_for(std::chrono::milliseconds(x));
}

// END BUS MANAGMENT INTERFACE 1.0
// 🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌🚌