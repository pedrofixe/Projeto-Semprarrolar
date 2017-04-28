#include "driver.h"

bool LoadDrivers(std::string filename) {
	std::ifstream driverstream(filename);
	if (driverstream.fail()) {
		driverstream.close();
		return false;
	}

	// Load drivers
	string tempdriver;
	while (getline(driverstream, tempstring)) {
		// LER LINHA DO FICHEIRO
		istringstream linha_stream(tempstring);
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
	driverstream.close();
	return true;
}