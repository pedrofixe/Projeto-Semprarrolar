#include "line.h"

void Line::SetID(const string& input)
{
	ID = input;
}

void Line::SetFreq(const unsigned int& input)
{
	freq = input;
}

void Line::SetBus_Stops(const vector<string>& input)
{
	bus_stops = input;
}

void Line::SetTimeBetweenStops(const vector<unsigned int>& input)
{
	timeBetweenStops = input;
}


string Line::GetID() const
{
	return ID;
}

unsigned int Line::GetFreq() const
{
	return freq;
}

const vector<string> Line::GetBus_Stops() const
{
	return bus_stops;
}

vector<unsigned int> Line::GetTimeBetweenStops() const
{
	return timeBetweenStops;
}


void Line::ShowSchedule() const
{
	//Show forward direction
	cout << setw(5) << "" << "Direction " << bus_stops[0] << " -> " << bus_stops[bus_stops.size() - 1] << " :" << endl << endl;
	PrintSpecificSchedule(bus_stops, timeBetweenStops, freq, 0);
	cout << endl << endl;

	//Show return direction
	vector<Paragem> vec_paragens = linha.paragens;
	vector<tempo_t> vec_tempoViagem = linha.tempoViagem;

	// // Calcular o offset inicial, isto é, o tempo que o primeiro autocarro do dia demora a fazer o percurso de ida
	const unsigned int offset = abs(CalculaOffset(vec_tempoViagem, vec_paragens.size() - 1));

	reverse(vec_paragens.begin(), vec_paragens.end()); // Alterar a ordem do vetor para o inverso para imprimir o horario de VOLTA
	reverse(vec_tempoViagem.begin(), vec_tempoViagem.end()); // ""
	cout << setw(5) << "" << "Direction " << bus_stops[linha.paragens.size() - 1] << " -> " << bus_stops[0] << " :" << endl << endl;
	ImprimirHorariosLinha(vec_paragens, vec_tempoViagem, linha.freq, offset);
}

void Line::PrintSpecificSchedule(const vector<string>& bus_stops, const vector<unsigned int>& timeBetweenStops, unsigned int freq, unsigned int offset)
{

}