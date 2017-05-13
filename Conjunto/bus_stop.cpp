#include "bus_stop.h"

const string& Bus_Stop::GetName() const
{
	return name;
}

unsigned int Bus_Stop::GetLinesCount() const
{
	return linesAtStop.size();
}

void Bus_Stop::RemoveLineFromStop(const Line *ptr_Line )
{
	auto iterator = find(linesAtStop.begin(), linesAtStop.end(), ptr_Line);
	if (iterator != linesAtStop.end()) { // found
		linesAtStop.erase(iterator);
	}
	//if it doesn't exist do nothing
}

const vector<Line*>& Bus_Stop::GetLines() const
{
	return linesAtStop;
}

void Bus_Stop::AddLine(Line * ptr_Line)
{
	linesAtStop.push_back(ptr_Line);
}

void Bus_Stop::ShowSchedule() const
{ // REQUIRES MASSIVE TRANSLATION TO ENGLISH ## WILL BE LEFT IN PORTUGUESE FOR THE TIME BEING
	//for (Line* linha : linesAtStop) { // Iterar sobre cada linha que passa na paragem.
	//	const unsigned int frequencia = linha->GetFreq(); // frequencia da linha
	//											//Calcular tempo entre a primeira paragem e a paragem que queremos obter os horarios
	//	const unsigned int numeroDaParagem = IndiceElemento(linha->paragens, par.first);
	//	const unsigned int offsetHorarios = CalculaOffset(linha->tempoViagem, numeroDaParagem);

	//	// Mostrar no sentido de ida
	//	if (par.first.nome != linha->paragens[linha->paragens.size() - 1].nome) {
	//		cout << setw(5) << "Horario da linha " << linha->ID << " no sentido " << linha->paragens[0].nome << " -> " << linha->paragens[linha->paragens.size() - 1].nome << " :" << endl;
	//		ImprimeHorarios(HORARIO_INICIO, HORARIO_FIM, offsetHorarios, frequencia);
	//	}

	//	if (par.first.nome != linha->paragens[0].nome) {
	//		cout << endl << endl;
	//		// Mostrar no sentido de volta
	//		const tempo_t tempoViagemTotal = CalculaOffset(linha->tempoViagem, linha->paragens.size() - 1);
	//		cout << setw(5) << "Horario da linha " << linha->ID << " no sentido " << linha->paragens[linha->paragens.size() - 1].nome << " -> " << linha->paragens[0].nome << " :" << endl;
	//		ImprimeHorarios(HORARIO_INICIO, HORARIO_FIM, tempoViagemTotal + (tempoViagemTotal - offsetHorarios), frequencia);
	//	}
	//}
	cout << "yy";
}

//int IndiceElemento(const vector<Paragem> &vec_paragens, const Paragem &paragem) {
//	for (size_t i = 0; i < vec_paragens.size(); i++) {
//		if (vec_paragens[i].nome == paragem.nome) {
//			return i;
//		}
//	}
//	return -1; // vamos esperar que isto nao aconteça...
//}