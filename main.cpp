#include<iostream>
#include "file.cpp"
using namespace std;

int main(){
    int tmp; 
    cout<<"Vuoi caricare le informazioni da un file? Y:1 N:0 ";
    cin>>tmp;
    Albergo a;
    if(tmp==1){
        a.carica(tmp);
    }
    if(tmp==2||tmp==0){
        cin>>a;
    }

    string nm, cg;
    bool j=true; //Variabile di fine ciclo
    
    

    do{
        cout<<"Cosa vuoi fare?"<<endl;
        cout<<"  Stampa delle informazioni:0"<<endl;
        cout<<"  Aggiungi un cliente:1"<<endl;
        cout<<"  Cancella un cliente:2"<<endl;
        cout<<"  Aggiungi un dipendente:3"<<endl;
        cout<<"  Cancella un dipendente:4"<<endl;
        cout<<"  Stanze occupate:5"<<endl;
        cout<<"  Uscire:6"<<endl;
        cin>>tmp;
        switch(tmp){
            case 0:
                {
                cout<<"Quali informazioni vuoi stampare?"<<endl;
                cout<<"  Albergo:1"<<endl;
                cout<<"  Stanze:2"<<endl;
                cout<<"  Clienti:3"<<endl;
                cout<<"  Dipendenti:4"<<endl;
                int print=0;
                do{
                    cout<<"Inserire uno dei numeri: ";
                    cin>>tmp;
                }while(tmp>4||tmp<1);
                switch(tmp){
                    case 1:
                        cout<<a;
                    break;

                    case 2:
                        a.show_stanze();
                    break;

                    case 3:
                        cout<<"In che ordine visualizzarli?"<<endl;
                        cout<<"Alfabetico:1  Stanza:2  Giorni Asc:3  Giorni Desc:4 "<<endl;
                        do{
                            cout<<"Inserire uno dei numeri: ";
                            cin>>tmp;
                        }while(tmp>4||tmp<1);
                        a.show_clienti(tmp);
                    break;

                    case 4:
                        cout<<"In che ordine visualizzarli?"<<endl;
                        cout<<"Alfabetico:1  Salariale:2  Occupazione:3 "<<endl;
                        do{
                            cout<<"Inserire uno dei numeri: ";
                            cin>>tmp;
                        }while(tmp>3||tmp<1);
                        a.show_dipendenti(tmp);
                    break;
                }
                }
            break;

            case 1:
                a.add_cliente();
            break;
            
            case 2:
                a.delete_cliente();
            break;
            
            case 3:
                a.add_dipendente();
            break;

            case 4:
                a.delete_dipendente();
            break;

            case 5:
                a.stanze_occupate();
            break;

            case 6:
            {
                int tmp=0;
                do{
                    cout<<"Salvare i dati su un file? Y:1 N:0 ";
                    cin>>tmp;
                }while(tmp!=0&&tmp!=1);
                if(tmp==1){
                    a.salva();
                }
                j=false;
                cout<<"*********************************************"<<endl;
                cout<<"|Chiusura del programa effettuata: A presto.|"<<endl;
                cout<<"*********************************************"<<endl;
            }
            break;

            default:
            break;
 
        }
    }while(j);
    return 0;
}
