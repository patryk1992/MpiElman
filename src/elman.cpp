#include "elman.h"


elman::elman(int iloscTestow, int neuronyWeWy, int neuronyUkryte, int tempoNauki, char* wejscie)
{
	srand (static_cast <unsigned> (time(0)));
	NEURONY_WEJSCIOWE = neuronyWeWy;
	int counter = strlen(wejscie)/NEURONY_WEJSCIOWE;
	ctrD = counter;
	_przyklad = new double*[counter];

	for(int i=0;i<counter;i++)
	{
		_przyklad[i] = new double(neuronyWeWy);
	}
	MAX_PRZYKLADOW = counter + 1;
	NEURONY_WYJSCIOWE = neuronyWeWy;
	_tablica = new double[neuronyWeWy];

	for (int i = 0; i < NEURONY_WEJSCIOWE; i++)
    {
        if (i == 0) _tablica[i] = 1.0;
        else _tablica[i] = 0.0;
    }
	MAX_TESTOW = iloscTestow;
	NEURONY_UKRYTE = neuronyUkryte;
	NEURONY_KONTEKSTOWE = neuronyUkryte;
	TEMPO_NAUKI = tempoNauki;
	ILOSC_POWTORZEN_TRENINGOWYCH = 4000;

	WejscioweDoUkrytych = new double*[NEURONY_WEJSCIOWE+1];
	for(int i =0;i<NEURONY_WEJSCIOWE+1;i++)
	{
		WejscioweDoUkrytych[i] = new double[NEURONY_UKRYTE];
	}

	KontekstoweDoUkrytych = new double*[NEURONY_KONTEKSTOWE+1];
	for(int i =0;i<NEURONY_KONTEKSTOWE+1;i++)
	{
		KontekstoweDoUkrytych[i] = new double[NEURONY_UKRYTE];
	}

	UkryteDoWyjsciowych = new double*[NEURONY_UKRYTE+1];
	for(int i =0;i<NEURONY_UKRYTE+1;i++)
	{
		UkryteDoWyjsciowych[i] = new double[NEURONY_WYJSCIOWE];
	}

	UkryteDoKontekstowych = new double*[NEURONY_WYJSCIOWE+1];
	for(int i =0;i<NEURONY_WYJSCIOWE+1;i++)
	{
		UkryteDoKontekstowych[i] = new double[NEURONY_KONTEKSTOWE];
	}

	wejscia = new double[NEURONY_WEJSCIOWE];
	ukryte = new double[NEURONY_UKRYTE];
	wynikowe = new double[NEURONY_WYJSCIOWE];
	aktualne = new double[NEURONY_WYJSCIOWE];
	kontekstowe = new double[NEURONY_KONTEKSTOWE];
	bledyWyjsciowe = new double[NEURONY_WYJSCIOWE];
	bledyUkryte = new double[NEURONY_UKRYTE];

	for (int j = 0; j < counter; j++)
	{
		for (int i = 0; i < NEURONY_WYJSCIOWE; i++)
		{
			
			double ttmp = std::strtod(&wejscie[j*NEURONY_WEJSCIOWE+i],NULL);//Double.Parse(tmp[j * NEURONY_WYJSCIOWE + i]);
			_przyklad[j][i] = ttmp;
		}           
	}

	/*sw = new char[1];
	sw2 = new char[1];
	sw3 = new char[1];*/

	sww = new std::string;
	sww2 = new std::string;
	sww3 = new std::string;
}

void elman::elmanNetwork()
    {

        double blad = 0.0;
        int przyklad = 0;
        int iteracje = 0;
        bool koniecPetli = false;
        
		//strcat(sw,"###TRENOWANIE###\n");

		sww->append("###TRENOWANIE###\n");
        przypiszLosoweWagi();

        while (!koniecPetli)
        {
            if (przyklad == 0)
            {
                for (int i = 0; i < NEURONY_WEJSCIOWE; i++)
                {
                    wejscia[i] = _tablica[i];
                }
            }

            else
            {
                for (int i = 0; i < NEURONY_WEJSCIOWE; i++)
                {
                    wejscia[i] = _przyklad[przyklad - 1][ i];

                }
            }

            if (przyklad == MAX_PRZYKLADOW - 1)
            {
                for (int i = 0; i < NEURONY_WEJSCIOWE; i++)
                {
                    wynikowe[i] = _tablica[i];
                }
            }
            else
            {
                for (int i = 0; i < NEURONY_WEJSCIOWE; i++)
                {
                    wynikowe[i] = _przyklad[przyklad][i];
                }
            }

            sprzezeniePrzod();

            blad = 0.0;
            for (int i = 0; i < NEURONY_WYJSCIOWE; i++)
            {
				blad += sqrt(wynikowe[i] - aktualne[i]);
            }
            blad = 0.5 * blad;

            if (iteracje > ILOSC_POWTORZEN_TRENINGOWYCH)
            {
                koniecPetli = true;
            }
            iteracje++;

            przypiszLosowaLiczbe();

            przyklad++;
            if (przyklad == MAX_PRZYKLADOW)
            {
                przyklad = 0;
            }
        }

		//strcat(sw,"Liczba iteracji = ");
		//strcat(sw,toString(iteracje));
		//strcat(sw,"###KONIEC TRENOWANIA###\n");
		sww->append("Liczba iteracji = "+toString(iteracje)+"\n###KONIEC TRENOWANIA###\n");
        return;
    }


void elman::testNetwork()
    {

        int indeks = 0;
        int losowaLiczba = 0;
        int przewidywana = 0;
        bool stopPrzykladu = false;
        bool sukces = false;
        //Decimal dfm = 0;
		float dfm = 0;

		//strcat(sw,"###start sieci###\n"); //ew const char *strFrom = "###start sieci###\n";
		sww->append("###start sieci###\n");

        for (int test = 0; test < MAX_TESTOW; test++)
        {
            while ((znak == false) && !Krok)
            {

            }
            if (znak == false)
            {

                Krok = false;
            }

            if ((test == 0) && znak)
            { }

			//strcat(sw,"\nWejscie:(0)\n");
			sww->append("\nWejscie:(0)\n");

            sprzezeniePrzod();

            stopPrzykladu = false;
            sukces = false;
            indeks = 0;
            losowaLiczba = 0;
            przewidywana = 0;

            while (stopPrzykladu == false)
            {

                
				//strcat(sw,"Wejscie\t| szansa %:");
				sww->append("Wejscie\t| szansa %:");

                for (int i = 0; i < NEURONY_WYJSCIOWE; i++)
                {
					//strcat(sw,"\n");
					sww->append("\n");

                    dfm = aktualne[i];
                    //sw += i + "\t| " + Math.Round(dfm, 3) + " " + "\t"; c#

					//strcat(sw,toString(i));
					//strcat(sw,"\t| ");
					//strcat(sw,toString((myRoundD(dfm*1000)/1000)));
					//strcat(sw," \t");

					sww->append(toString(i)+"\t| ");
					sww->append(toString((myRoundD(dfm*1000)/1000)));

					if (MaxD(aktualne,NEURONY_WYJSCIOWE) == aktualne[i])
                    {
						//strcat(sw," <=Przewidziana\n");
						sww->append(" <=Przewidziana\n");

                    }
                    else
                    {
                        //strcat(sw,"\n");
						sww->append("\n");

                    }

                    if (aktualne[i] > 0.3)
                    {

                        przewidywana = i;

                    }

                }

                //strcat(sw,"\n");
				sww->append("\n");


                indeks++;
                if (indeks == NEURONY_WYJSCIOWE - 1)
                {
                    stopPrzykladu = true;

                }

                losowaLiczba = getRandomNumber();
                if (stopPrzykladu != true)
                {
                    //sw += "Wejscie" + "(" + losowaLiczba + ") \n"; c#

					//strcat(sw,"Wejscie(");
					//strcat(sw,toString(losowaLiczba));
					//strcat(sw,")\n");

					sww->append("Wejscie("+toString(losowaLiczba)+")\n");
                }
                for (int i = 0; i < NEURONY_WEJSCIOWE; i++)
                {
                    if (i == losowaLiczba)
                    {
                        wejscia[i] = 1.0;
                        if (i == przewidywana)
                        {
                            sukces = true;
                        }
                        else
                        {
                            stopPrzykladu = true;
                        }
                    }
                    else
                    {
                        wejscia[i] = 0.0;
                    }
                }

                sprzezeniePrzod();

            }

            if ((indeks > NEURONY_WYJSCIOWE - 2) && (sukces == true))
            {
                //sw += "Sukces."; C#
                //sw += "Wykonano " + test + " testów.";

				/*strcat(sw,"Sukces.");
				strcat(sw,"Wykonano ");
				strcat(sw,toString(test));
				strcat(sw," testow");*/
				sww->append("Sukces.\nWykonano "+toString(test)+" testow");

				sww3->append("Sukces!\nWykonano "+toString(test)+" testow");
                //sw3 = "Sukces!\nWykonano ";// + test + " testów."; c#
				//strcat(sw3,toString(test));
				//strcat(sw3," testow");

                break;
            }
            else
            {
                //sw += "\nNiepowodzenie.";
				//strcat(sw,"\nNiepowodzenie.");
				sww->append("\nNiepowodzenie.");
                if (test > MAX_TESTOW)
                {
                    //sw += "Wykonano" + test + " testów bez sukcesu.";
					//strcat(sw,"Wykonano ");
					//strcat(sw,toString(test));
					//strcat(sw," testow bez sukcesu");
					sww->append("Wykonano "+toString(test)+" testow bez sukcesu");
					sww2->append(sww->c_str());
					//strcat(sw2,sw);

					//delete[] sw;
					//sw=new char[1];
					sww->clear();

                    break;
                }
            }
            //strcat(sw2,sw);
			sww2->append(sww->c_str());
			sww->clear();
			//delete[] sw;
			///sw=new char[1];
        }
        
        return;
    }

void elman::sprzezeniePrzod()
    {
        double sum = 0.0;

        for (int hid = 0; hid < NEURONY_UKRYTE; hid++)
        {
            sum = 0.0;
            for (int inp = 0; inp < NEURONY_WEJSCIOWE; inp++)
            {
                sum += wejscia[inp] * WejscioweDoUkrytych[inp][hid];
            }

            for (int con = 0; con < NEURONY_KONTEKSTOWE; con++)
            {
                sum += kontekstowe[con] * KontekstoweDoUkrytych[con][hid];
            }

            sum += WejscioweDoUkrytych[NEURONY_WEJSCIOWE][hid];   
            sum += KontekstoweDoUkrytych[NEURONY_KONTEKSTOWE][hid];
            ukryte[hid] = sigmoid(sum);
        } 

        for (int out1 = 0; out1 < NEURONY_WYJSCIOWE; out1++)
        {
            sum = 0.0;
            for (int hid = 0; hid < NEURONY_UKRYTE; hid++)
            {
                sum += ukryte[hid] * UkryteDoWyjsciowych[hid][out1];
            } 

            sum += UkryteDoWyjsciowych[NEURONY_UKRYTE][out1];  
            aktualne[out1] = sigmoid(sum);
        } 

        for (int con = 0; con < NEURONY_KONTEKSTOWE; con++)
        {
            kontekstowe[con] = ukryte[con];
        }
        return;
    }

void elman::przypiszLosowaLiczbe()
    {
        for (int out1 = 0; out1 < NEURONY_WYJSCIOWE; out1++)
        {
            bledyWyjsciowe[out1] = (wynikowe[out1] - aktualne[out1]) * sigmoidDerivative(aktualne[out1]);
        }

        for (int hid = 0; hid < NEURONY_UKRYTE; hid++)
        {
            bledyUkryte[hid] = 0.0;
            for (int out1 = 0; out1 < NEURONY_WYJSCIOWE; out1++)
            {
                bledyUkryte[hid] += bledyWyjsciowe[out1] * UkryteDoWyjsciowych[hid][out1];
            } 
            bledyUkryte[hid] *= sigmoidDerivative(ukryte[hid]);
        }

        for (int out1 = 0; out1 < NEURONY_WYJSCIOWE; out1++)
        {
            for (int hid = 0; hid < NEURONY_UKRYTE; hid++)
            {
                UkryteDoWyjsciowych[hid][out1] += (TEMPO_NAUKI * bledyWyjsciowe[out1] * ukryte[hid]);
            }

            UkryteDoWyjsciowych[NEURONY_UKRYTE][out1] += (TEMPO_NAUKI * bledyWyjsciowe[out1]);
        }

        for (int hid = 0; hid < NEURONY_UKRYTE; hid++)
        {
            for (int inp = 0; inp < NEURONY_WEJSCIOWE; inp++)
            {
                WejscioweDoUkrytych[inp][hid] += (TEMPO_NAUKI * bledyUkryte[hid] * wejscia[inp]);
            } 

            WejscioweDoUkrytych[NEURONY_WEJSCIOWE][hid] += (TEMPO_NAUKI * bledyUkryte[hid]); 
        } 
        return;
    }

void elman::przypiszLosoweWagi()
    {
        for (int inp = 0; inp <= NEURONY_WEJSCIOWE; inp++)  
        {
            for (int hid = 0; hid < NEURONY_UKRYTE; hid++)
            {
				WejscioweDoUkrytych[inp][hid] = getRandomDouble() - 0.5;
            } 
        } 

        for (int con = 0; con <= NEURONY_KONTEKSTOWE; con++)
        {
            for (int hid = 0; hid < NEURONY_UKRYTE; hid++)
            {
                KontekstoweDoUkrytych[con][hid] = getRandomDouble() - 0.5;
            } 
        } 

        for (int hid = 0; hid <= NEURONY_UKRYTE; hid++)  
        {
            for (int out1 = 0; out1 < NEURONY_WYJSCIOWE; out1++)
            {
                UkryteDoWyjsciowych[hid][out1] = getRandomDouble() - 0.5;
            } 
        } 

        for (int out1 = 0; out1 <= NEURONY_WYJSCIOWE; out1++)
        {
            for (int con = 0; con < NEURONY_KONTEKSTOWE; con++)
            {
                UkryteDoKontekstowych[out1][con] = 0.5;
            } 
        } 
        return;
    }


elman::~elman(void)
{
	sww2->clear();
	sww->clear();
	sww3->clear();

	delete sww;
	delete sww2;
	delete sww3;
	/*for(int i=0;i<ctrD;i++)
	{
		delete[] _przyklad[i];
	}*/

	delete[] _przyklad;
	//delete[] _tablica;

	for(int i =0;i<NEURONY_WEJSCIOWE+1;i++)
	{
		delete[] WejscioweDoUkrytych[i];
	}
	delete[] WejscioweDoUkrytych;

	
	for(int i =0;i<NEURONY_KONTEKSTOWE+1;i++)
	{
		delete[] KontekstoweDoUkrytych[i];
	}
	delete[] KontekstoweDoUkrytych;
	
	for(int i =0;i<NEURONY_UKRYTE+1;i++)
	{
		delete[] UkryteDoWyjsciowych[i];
	}
	delete[] UkryteDoWyjsciowych;

	for(int i =0;i<NEURONY_WYJSCIOWE+1;i++)
	{
		delete[] UkryteDoKontekstowych[i];
	}
	delete[] UkryteDoKontekstowych;

	delete[] wejscia;
	delete[] ukryte;
	delete[] wynikowe;
	delete[] aktualne;
	delete[] kontekstowe;
	delete[] bledyWyjsciowe;
	delete[] bledyUkryte;

}
