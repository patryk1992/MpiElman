#pragma once
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <string.h>
#include <cmath>
#include <sstream>


class elman
{
public:
	elman(int iloscTestow, int neuronyWeWy, int neuronyUkryte, double tempoNauki, double** wejscie);
	~elman(void);
	void testNetwork(int* losowaLiczba);
	void elmanNetwork();

private:
         double* _tablica;
         double** _przyklad;
         int MAX_TESTOW;
         int MAX_PRZYKLADOW;
         int NEURONY_WEJSCIOWE;
         int NEURONY_UKRYTE;
         int NEURONY_WYJSCIOWE;
         int NEURONY_KONTEKSTOWE;
         double TEMPO_NAUKI;
         int ILOSC_POWTORZEN_TRENINGOWYCH;
         bool Krok;// = false;
         bool znak;// = false;
         double** WejscioweDoUkrytych;
         double** KontekstoweDoUkrytych;
         double** UkryteDoWyjsciowych;
         double** UkryteDoKontekstowych;

         double* wejscia;
         double* ukryte;
         double* wynikowe;
         double* aktualne;
         double* kontekstowe;

         double* bledyWyjsciowe;
         double* bledyUkryte;

		 int ctrD;
         /*string sw = null;
         string sw2 = null;
         string sw3 = null;*/
		 char* sw;
		 char* sw2;
		 char* sw3;
		 std::string* sww;
		 std::string* sww2;
		 std::string* sww3;
	
	int getRandomNumber()
	{
		return rand() % NEURONY_WEJSCIOWE; //ew NEURONYWEJSCIOWE +1 jesli ta warto�� ma by� losowana
	}

	double sigmoid(double val)
	{
		return (1.0 / (1.0 + exp(-val)));
	}

	double sigmoidDerivative(double val)
	{
		return (val * (1.0 - val));
	}

	double getRandomDouble()
	{
		return static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	}

	
	void przypiszLosoweWagi();
	void przypiszLosowaLiczbe();
	void sprzezeniePrzod();
	

	//template<class T>
	/*char* toString(int val)
	{
		std::stringstream ss;
		ss << val;

		char* char_type = new char[ss.str().length()];
		strcpy(char_type, ss.str().c_str());
		char_type[ss.str().length()]='\0';
		return char_type;
	}*/
	std::string toString(double val)
	{
		std::stringstream ss;
		ss << val;
		return ss.str();
	}

	std::string toString(int val)
	{
		std::stringstream ss;
		ss << val;
		return ss.str();
	}
	/*char* toString(double val)
	{
		std::stringstream ss;
		ss << val;

		char* char_type = new char[ss.str().length()];
		strcpy(char_type, ss.str().c_str());

		return char_type;
	}
	char* toString(float val)
	{
		std::stringstream ss;
		ss << val;

		char* char_type = new char[ss.str().length()];
		strcpy(char_type, ss.str().c_str());

		return char_type;
	}*/

	double myRoundD( double fValue)
	{
		return fValue < 0 ? ceil( fValue - 0.5 )
			: floor( fValue + 0.5 );
	}

	double MaxD(double *tab, int count)
	{
		double max = tab[0];
		for(int i=1;i<count;i++)
		{
			if(tab[i]>max)
			{
				max=tab[i];
			}
		}
		return max;
	}
};

