#include <iostream>
#include "header.h"
#include <fstream>
using namespace std;


//** ************** FUNZIONI AUSILIARIE ************** **

/**
 * \fn bool find(int *arr, int size, int elem)
 * \brief Cerca un elemento in un array
 * \return bool
 * \author Achille Cannavale
 * \file file.cpp
 */
bool find(int *arr, int size, int elem){
    for(int i=0; i<size; i++){
        if(arr[i]==elem){
            return true;
        }
    }
    return false;
}

/**
 * \fn void swapDip(Dipendente *a, Dipendente *b)
 * \brief Scambia di posto due puntatori a dipendente
 * \return void
 * \author Achille Cannavale
 * \file file.cpp
 */
void swapDip(Dipendente *a, Dipendente *b){
    Dipendente tmp=*a;
   *a=*b;
    *b=tmp;
    return;
}

/**
 * \fn void swapCl(Cliente *a, Cliente *b)
 * \brief Scambia di posto due puntatori a cliente
 * \return void
 * \author Achille Cannavale
 * \file file.cpp
 */
void swapCl(Cliente *a, Cliente *b){
    Cliente tmp=*a;
   *a=*b;
   *b=tmp;
    return;
}


//** ************** ALBERGO ************** **
 /**
 * \fn Albergo::Albergo()
 * \brief Costruttore della classe Albergo
 * \return
 * \author Achille Cannavale
 * \file file.cpp
 */
Albergo::Albergo(){
    denominazione="";
    luogo="";
    stelle="";
    Nstanze=0;
    Ndipendenti=0;
    v = new Stanza*[Nstanze];
    d= new Dipendente*[Ndipendenti];
}


/**
 * \fn bool Albergo::full()
 * \brief Controlla se l'albergo è pieno
 * \return bool
 * \author Achille Cannavale
 * \file file.cpp
 */
bool Albergo::full(){
    int sum=0;
    for(int i=0;i<Nstanze;i++){
        if(v[i]->get_occupanti()>0){
            sum++;
        }
    }
    if(sum==Nstanze){
        return true;
    }else{
        return false;
    }
}

/**
 * \fn bool Albergo::Dempty()
 * \brief Controlla se ci sono dipendenti
 * \return bool
 * \author Achille Cannavale
 * \file file.cpp
 */
bool Albergo::Dempty(){
    if(Ndipendenti==0){
        return true;
    }else{
        return false;
    }
}

/**
 * \fn bool Albergo::empty()
 * \brief Controlla se l'albergo è vuoto
 * \return bool
 * \author Achille Cannavale
 * \file file.cpp
 */
bool Albergo::empty(){ //L'Albergo è vuoto?
    int sum=0;
    for(int i=0;i<Nstanze;i++){
        sum+=v[i]->get_occupanti();
    }
    if(sum==0){
        return true;
    }else{
        return false;
    }
}

/**
 * \fn void Albergo::show_stanze()
 * \brief Stampa le informazioni di tutte le stanze
 * \return void
 * \author Achille Cannavale
 * \file file.cpp
 */
void Albergo::show_stanze(){
    for(int i=0; i<Nstanze; i++){
        cout<<*(v[i])<<endl;
    }
    return;
}

/**
 * \fn void Albergo::add_cliente()
 * \brief Aggiunge un cliente in una stanza libera a scelta
 * \return void
 * \author Achille Cannavale
 * \file file.cpp
 */
void Albergo::add_cliente(){//Aggiungi un cliente se possibile
    if(!full()){
        int x=0;
        cout<<"Sono libere le stanze: ";
        int c=0;
        int *tmp= new int[Nstanze];
        for(int i=0; i<Nstanze;i++){
            if(v[i]->get_occupanti()==0){    
                tmp[c]=v[i]->get_numero();
                c++;
            }
        }
        for(int i=0; i<c;i++){
            cout<<tmp[i]<<"; "<<endl;
        }
        do{
            cout<<"In quel stanza assegnarlo?"<<endl;
            cin>>x;
        }while(!find(tmp, c, x));
        x--;
        v[x]->c[v[x]->get_occupanti()]=new Cliente();
        v[x]->c[v[x]->get_occupanti()]->set_Nstanza(v[x]->get_numero());
        v[x]->set_occupanti((v[x]->get_occupanti()+1));
        cout<<"******************************************"<<endl;
        cout<<"|Operazione effettuata: Cliente aggiunto.|"<<endl;
        cout<<"******************************************"<<endl;
        delete[] tmp;
        return;
    }else{
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        cout<<"|Errore: l'albergo e' pieno.|"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        return;
    }
}

/**
 * \fn void Albergo::delete_cliente(string nm="pippo", string cg="pluto")
 * \brief Cancella un cliente
 * \return void
 * \author Achille Cannavale
 * \file file.cpp
 */
void Albergo::delete_cliente(string nm="pippo", string cg="pluto"){//Cancella un cliente se possibile
    if(!empty()){
        bool check=false;
        if(nm=="pippo"&&cg=="pluto"){
            cout<<"Inserisci il nome del cliente da cancellare: ";
            cin>>nm;
            cout<<"Inserisci il cognome del cliente da cancellare: ";
            cin>>cg;
            check=true;
        }
        for(int i=0; i<Nstanze;i++){
            for(int j=0; j<v[i]->get_occupanti();j++){
                if(((v[i]->c[j]->get_nome())==nm)&&((v[i]->c[j]->get_cognome())==cg)){
                    if(check){
                        int choise;
                        cout<<"Stampare la fattura del cliente prima di eliminarlo? Y:1 N:0 ";
                        cin>>choise;
                        if(choise==1){
                            cout<< "%%%%%%%%%%%%%%%SCONTRINO FISCALE%%%%%%%%%%%%%%%%%" <<endl;
                            cout<< "%%%%% "<<nm<<" "<<cg<<" SUMMARY DATA %%%%%" <<endl;
                            cout<< "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" <<endl;
                            cout<< "%%%% Giorni di permanenza ..... = " << v[i]->c[j]->get_permanenza()<<endl;
                            cout<< "%%%% Costo totale ............. = " << (v[i]->get_prezzo()*v[i]->c[j]->get_permanenza())<<endl;
                            cout<< "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
                            cout<< "%%%%%%%%%%%%%%GRAZIE E ARRIVEDERCI%%%%%%%%%%%%%%%" << endl;
                        }
                    }
                    for(int k=j; k<(v[i]->get_occupanti()-1);k++){
                        v[i]->c[k]=v[i]->c[k+1];
                    }  
                    v[i]->set_occupanti((v[i]->get_occupanti()-1));
                    cout<<"********************************************"<<endl;
                    cout<<"|Operazione effettuata: Cliente cancellato.|"<<endl;
                    cout<<"********************************************"<<endl;
                    return;
                } 
            }
        }
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        cout<<"|Errore: non esiste alcun cliente con questo nome.|"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        return;
    }else{
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        cout<<"|Errore: non esiste alcun cliente.|"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        return;
    }
}

/**
 * \fn int Albergo::Nclienti()
 * \brief Conta quanti clienti sono presenti nell'albergo
 * \return int
 * \author Achille Cannavale
 * \file file.cpp
 */
int Albergo::Nclienti(){
    if(!empty()){
        int sum=0;
        for(int i=0;i<Nstanze;i++){
            sum+=(v[i]->get_occupanti());
        }
        return sum;
    }else{
        return 0;
    }
}

/**
 * \fn void Albergo::show_clienti()
 * \brief Mostra le informazioni dei clienti nell'albergo in ordine a scelta
 * \return void
 * \author Achille Cannavale
 * \file file.cpp
 */
void Albergo::show_clienti(int ordine){
    //Per l'ordinamento ho optato per un Bubble sort con sentinella
    if(!empty()){
        int size = Nclienti();
        int l=0;
        Cliente **tmp=new Cliente*[size];
        for(int i=0; i<Nstanze; i++){
            for(int j=0; j<(v[i]->get_occupanti()); j++){
                tmp[l]=v[i]->c[j];
                l++;
            }
        }
        switch(ordine){
            case 1:
            {
                int k;
                do{
		            k=0;
		            for(int i=0;i<size-1;i++){
			            if(tmp[i]->get_cognome()>tmp[i+1]->get_cognome()){
				            swapCl(tmp[i],tmp[i+1]);
				            k=1;
			            }
                    }
	            }while (k==1);
                
            }
            break;
            case 2:
            {
                int k;
                do{
		            k=0;
		            for(int i=0;i<size-1;i++){
			            if(tmp[i]->get_Nstanza()>tmp[i+1]->get_Nstanza()){
				            swapCl(tmp[i],tmp[i+1]);
				            k=1;
			            }
                    }
	            }while (k==1);

            }
            break;
            case 3:
            {
                int k;
                do{
		            k=0;
		            for(int i=0;i<size-1;i++){
                        
			            if((tmp[i]->get_permanenza())>(tmp[i+1]->get_permanenza())){
                            cout<<tmp[i]->get_permanenza();
				            swapCl(tmp[i],tmp[i+1]);
				            k=1;
			            }
                    }
	            }while (k==1);

            }
            break;
            case 4:
            {
                int k;
                do{
		            k=0;
		            for(int i=0;i<size-1;i++){
			            if(tmp[i]->get_permanenza()<=tmp[i+1]->get_permanenza()){
				            swapCl(tmp[i],tmp[i+1]);
				            k=1;
			            }
                    }
	            }while (k==1);

            }
            break; 
        }
        for(int i=0; i<size;i++){
                cout<<*(tmp[i]);
        }

        for(int i=0; i<l; i++){
            tmp[i]=NULL;
        }
        delete [] tmp;
    }else{
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        cout<<"|Errore: l'albergo e' vuoto.|"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    }
    return;
}

/**
 * \fn void Albergo::emettiFile(ofstream &of,string nm, string cg,int i, int j)
 * \brief Stampa su file la fattura di un determinato cliente, calcolando il totale da pagare
 * \return void
 * \author Achille Cannavale
 * \file  file.cpp
 */
void Albergo::emettiFile(ofstream &of,string nm, string cg,int i, int j){
    of<< "%%%%%%%%%%%%%%%SCONTRINO FISCALE%%%%%%%%%%%%%%%%%" <<endl;
    of<< "%%%%% "<<nm<<" "<<cg<<" SUMMARY DATA %%%%%" <<endl;
    of<< "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" <<endl;
    of<< "%%%% Giorni di permanenza ..... = " << v[i]->c[j]->get_permanenza()<<endl;
    of<< "%%%% Costo totale ............. = " << (v[i]->get_prezzo()*v[i]->c[j]->get_permanenza())<<endl;
    of<< "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    of<< "%%%%%%%%%%%%%%GRAZIE E ARRIVEDERCI%%%%%%%%%%%%%%%" << endl;
    return;
}


/**
 * \fn void Albergo::add_dipendente()
 * \brief Aggiunge un dipendente
 * \return void
 * \author Achille Cannavale
 * \file file.cpp
 */
void Albergo::add_dipendente(){//Aggiungi un dipendente
        d[Ndipendenti]=new Dipendente();
        Ndipendenti++;
        cout<<"*********************************************"<<endl;
        cout<<"|Operazione effettuata: Dipendente aggiunto.|"<<endl;
        cout<<"*********************************************"<<endl;
    return;
}

/**
 * \fn void Albergo::delete_dipendente()
 * \brief  Cancella un dipendente
 * \return void
 * \author Achille Cannavale
 * \file file.cpp
 */
void Albergo::delete_dipendente(){//Cancella un dipendente se possibile
    if(Dempty()){
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        cout<<"|Errore: non esiste alcun dipendente.|"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        return;
    }else{
        string nm,cg;
        cout<<"Inserisci il nome del dipendente da cancellare: ";
        cin>>nm;
        cout<<"Inserisci il cognome del dipendente da cancellare: ";
        cin>>cg;
        for(int i=0; i<Ndipendenti; i++){
            if(d[i]->get_nome()==nm&&d[i]->get_cognome()==cg){
                for(int j=0; j<Ndipendenti-1;j++){
                    d[i]=d[i+1];  
                }
                Ndipendenti--;
                cout<<"***********************************************"<<endl;
                cout<<"|Operazione effettuata: Dipendente cancellato.|"<<endl;
                cout<<"***********************************************"<<endl;
                return;
            }
        }
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        cout<<"|Errore: dipendente non trovato.|"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        return;
    } 
}

/**
 * \fn void Albergo::show_dipendenti(int ordine)
 * \brief Mostra le informazioni relative a tutti i dipendenti dell'Albergo, nell'ordine scelto
 * \return void
 * \author Achille Cannavale
 * \file file.cpp
 */
void Albergo::show_dipendenti(int ordine){
    //Per l'ordinamento ho optato per un Bubble sort con sentinella
    if(!Dempty()){
        switch(ordine){
            case 1:
            {
                int k;
                do{
		            k=0;
		            for(int i=0;i<Ndipendenti-1;i++){
			            if(d[i]->get_cognome()>d[i+1]->get_cognome()){
				            swapDip(d[i],d[i+1]);
				            k=1;
			            }
                    }
	            }while (k==1);

            }
            break;
            case 2:
            {
                int k;
                do{
		            k=0;
		            for(int i=0;i<Ndipendenti-1;i++){
			            if(d[i]->get_salario()>d[i+1]->get_salario()){
				            swapDip(d[i],d[i+1]);
				            k=1;
			            }
                    }
	            }while (k==1);

            }
            break;
            case 3:
            {
                int k;
                do{
		            k=0;
		            for(int i=0;i<Ndipendenti-1;i++){
			            if(d[i]->get_occupazione()>d[i+1]->get_occupazione()){
				            swapDip(d[i],d[i+1]);
				            k=1;
			            }
                    }
	            }while (k==1);
            }
            break;
        }
        for(int i=0; i<Ndipendenti;i++){
            cout<<*d[i];
        }
        return;
    }else{
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        cout<<"|Errore: l'albergo non ha dipendenti.|"<<endl;
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
        return;
    }
}

/**
 * \fn void Albergo::stanze_occupate()
 * \brief Mostra quante e quali stanze sono occupate
 * \return void
 * \author Achille Cannavale
 * \file file.cpp
 */
void Albergo::stanze_occupate(){
    int c=0;
    int *tmp= new int[Nstanze];
    for(int i=0; i<Nstanze;i++){
        if(v[i]->get_occupanti()!=0){    
            tmp[c]=v[i]->get_numero();
            c++;
        }
    }
    if(c==1){
        cout<<"E' occupata "<<c<<" stanza, ovvero: "<<endl;
    }else{
        cout<<"Sono occupate "<<c<<" stanze, ovvero: "<<endl;
    }
    for(int i=0; i<c;i++){
        cout<<"La stanza numero: "<<tmp[i]<<"; "<<endl;
    }
    delete[] tmp;
    return;
}

/**
 * \fn void Albergo::carica()
 * \brief Carica le informazioni dell'Albergo da un file definito dall'utente
 * \return void
 * \author Achille Cannavale
 * \file file.cpp
 */
void Albergo::carica(int &tmp){
    ifstream ifs;
    string filename;
    cout<<"Da quale file prendere le informazioni? ";
    cin>>filename;
    ifs.open(filename.c_str());
    if (!ifs.is_open()){
        cout<<"Problemi di apertura del file"<<endl;
        tmp=2;
        return;
    }
    
    string room, dip;
    ifs.clear();
    getline(ifs,denominazione,',');
    getline(ifs,luogo,',');
    getline(ifs,stelle,',');
    getline(ifs,room,',');
    Nstanze=atoi(room.c_str());
    getline(ifs,dip,',');
    Ndipendenti=atoi(dip.c_str());
    
    v = new Stanza*[Nstanze];
    
    for(int i=0; i<Nstanze; i++){
        string floor, number,bed, price, occ;
        ifs.ignore();
        getline(ifs, floor, ',');
        getline(ifs, number, ',');
        getline(ifs, bed, ',');
        getline(ifs, price, ',');
        getline(ifs, occ,',');
        v[i]=new Stanza(atoi(floor.c_str()),atoi(number.c_str()),atoi(bed.c_str()),atoi(price.c_str()),atoi(occ.c_str()));
                
        v[i]->c = new Cliente*[(v[i]->get_occupanti())];
        
        for(int j=0; j<(v[i]->get_occupanti()); j++){
            
            string nm, cg, ind, tel, perm;
            ifs.ignore();
            getline(ifs, nm, ',');
            getline(ifs, cg, ',');
            getline(ifs, ind, ',');
            getline(ifs, tel, ',');
            getline(ifs, perm, ',');

            v[i]->c[j]=new Cliente (nm, cg, ind, tel, atoi(perm.c_str()), v[i]->get_numero());
        }
        
    }

    d= new Dipendente*[Ndipendenti];
    for(int i=0; i<Ndipendenti;i++){
        string nm, cg, ind, tel, sal, temp, occ;
        bool b;
        ifs.ignore();
        getline(ifs, nm, ',');
        getline(ifs, cg, ',');
        getline(ifs, ind, ',');
        getline(ifs, tel, ',');
        getline(ifs, sal, ',');
        getline(ifs, occ, ',');
        getline(ifs, temp, ',');
        d[i]=new Dipendente(nm,cg,ind,tel,atoi(sal.c_str()),(b = (temp == "1")), occ );
    }
    cout<<"***************************************************"<<endl;
    cout<<"|Operazione effettuata: Dati caricati con successo.|"<<endl;
    cout<<"***************************************************"<<endl;
    return;
}

/**
 * \fn void Albergo::carica()
 * \brief Salva le informazioni dell'Albergo su un file definito dall'utente
 * \return void
 * \author Achille Cannavale
 * \file file.cpp
 */
void Albergo::salva(){
    ofstream ofs;
    string filename;
    cout<<"Inserisci il nome del file: ";
    cin>>filename;
    ofs.open(filename.c_str());
    if (!ofs.is_open()){
        cout<<"Problemi di apertura del file"<<endl;
        return;
    }
    ofs<<denominazione<<",";
    ofs<<luogo<<",";
    ofs<<stelle<<",";
    ofs<<Nstanze<<",";
    ofs<<Ndipendenti<<","<<endl;

    for(int i=0; i<Nstanze; i++){
        ofs<<v[i]->get_piano()<<",";
        ofs<<v[i]->get_numero()<<",";
        ofs<<v[i]->get_Nletti()<<",";
        ofs<<v[i]->get_prezzo()<<",";
        ofs<<v[i]->get_occupanti()<<","<<endl;

        for(int j=0;j<v[i]->get_occupanti(); j++){
            ofs<<v[i]->c[j]->get_nome()<<",";
            ofs<<v[i]->c[j]->get_cognome()<<",";
            ofs<<v[i]->c[j]->get_indirizzo()<<",";
            ofs<<v[i]->c[j]->get_telefono()<<",";
            ofs<<v[i]->c[j]->get_permanenza()<<","<<endl;
        }
    }

    for(int i=0; i<Ndipendenti; i++){
        ofs<<d[i]->get_nome()<<",";
        ofs<<d[i]->get_cognome()<<",";
        ofs<<d[i]->get_indirizzo()<<",";
        ofs<<d[i]->get_salario()<<",";
        ofs<<d[i]->get_occupazione()<<",";
        ofs<<d[i]->get_tempoIndeterminato()<<",";
    }
    cout<<"***************************************************"<<endl;
    cout<<"|Operazione effettuata: Dati salvati con successo.|"<<endl;
    cout<<"***************************************************"<<endl;
    return;
}

/**
 * \fn istream& operator>>(istream& is, Albergo& a)
 * \brief Operatore di output dell'Albergo
 * \return istream
 * \author Achille Cannavale
 * \file file.cpp
 */
istream& operator>>(istream& is, Albergo& a){
    cout<<"Inserisci le informazioni riguardanti l'albergo: "<<endl;
    cin.ignore();
    cout<<"Denominazione: ";
    
    getline(is,a.denominazione);
    cout<<"Luogo: ";
    getline(is,a.luogo);
    cout<<"Stelle (inserisci un numero): ";
    is>>a.stelle;
    do{
        cout<<"Stanze (almeno una): ";
        is>>a.Nstanze;
    }while(a.Nstanze<1);
    for(int i=0; i<a.Nstanze; i++){
        a.v[i]=new Stanza();
    }
    cout<<"Numero Dipendenti: ";
    is>>a.Ndipendenti;
    for(int i=0; i<a.Ndipendenti; i++){
        a.d[i]=new Dipendente();
    }
    return is;
}

/** 
 * \fn ostream& operator<<(ostream& os,  const Albergo& a)
 * \brief Operatore di input dell'Albergo
 * \return ostream
 * \author Achille Cannavale
 * \file file.cpp
 */
ostream& operator<<(ostream& os,  const Albergo& a){//OUTPUT
    os<<"*********ALBERGO: "<<a.denominazione<<"*********"<<endl;
    os<<"Stelle: "<<a.stelle<<endl;
    os<<"Luogo: "<<a.luogo<<endl;
    os<<"Numero di stanze: "<<a.Nstanze<<endl;
    os<<"********************************************"<<endl;
    return os;
}


//** ************** STANZA ************** **
/**
 * \fn Stanza::Stanza()
 * \brief Costruttore della classe Stanza
 * \return
 * \author Achille Cannavale
 * \file file.cpp
 */
Stanza::Stanza(){//Costruttore
    cin>>*this;
}

/**
 * \fn Stanza::Stanza(int p, int nS, int nL,int pr)
 * \brief Costruttore Parametrizzato della classe Stanza
 * \return
 * \author Achille Cannavale
 * \file  file.cpp
 */
Stanza::Stanza(int p, int nS, int nL,int pr, int occ){ //Costruttore param.
    piano=p;
    numero=nS;
    Nletti=nL;
    prezzo=pr;
    occupanti=occ;
}

/**
 * \fn istream& operator>>(istream& is, Stanza& s)
 * \brief Operatore di input della classe Stanza
 * \return istream
 * \author Achille Cannavale
 * \file file.cpp
 */
istream& operator>>(istream& is, Stanza& s){//INPUT
    int x=0;
    int n;
    cout<<"Inserisci le informazioni riguardanti la stanza: "<<endl;
    cout<<"Piano: ";
    is>>s.piano;
    o=o+1;
    s.numero=o;
    cout<<"Nletti: ";
    is>>s.Nletti;
    cout<<"Prezzo a notte:";
    is>>s.prezzo;
    cout<<"Occupanti:";
    is>>s.occupanti;
    s.c = new Cliente*[s.occupanti];
    if(s.occupanti!=0){
        for(int i=0; i<s.occupanti; i++){
            s.c[i]=new Cliente();
            s.c[i]->set_Nstanza(s.numero);
        }
    }
    return is;
}

/**
 * \fn ostream& operator<<(ostream& os,  const Stanza& s)
 * \brief Operatore di output della classe Stanza
 * \return ostream
 * \author Achille Cannavale
 * \file file.cpp
 */
ostream& operator<<(ostream& os,  const Stanza& s){//OUTPUT
    os<<"--------Stanza numero "<<s.numero<<"--------------"<<endl;
    os<<"Piano: "<<s.piano<<endl;
    os<<"Numero letti: "<<s.Nletti<<endl;
    os<<"-------------------------------------------------------"<<endl;
    
    return os;
}


//** ************** PERSONA ************** **
/**
 * \fn Persona::Persona()
 * \brief Costruttore della classe Persona
 * \return 
 * \author Achille Cannavale
 * \file  file.cpp
 */
Persona::Persona(){
    nome="";
    cognome="";
    indirizzo="";
    telefono="";
}

/**
 * \fn string Persona::get_nome()
 * \brief Restituisce il nome della Persona
 * \return string
 * \author Achille Cannavale
 * \file file.cpp
 */
string Persona::get_nome(){
    return nome;
}

/**
 * \fn string Persona::get_cognome()
 * \brief Restituisce il cognome della Persona
 * \return string
 * \author Achille Cannavale
 * \file file.cpp
 */
string Persona::get_cognome(){
    return cognome;
}

/**
 * \fn string Persona::get_indirizzo()
 * \brief Restituisce l'indirizzo della Persona
 * \return string
 * \author Achille Cannavale
 * \file file.cpp
 */
string Persona::get_indirizzo(){
    return indirizzo;
}

/**
 * \fn string Persona::get_telefono()
 * \brief restituisce il telefono della Persona
 * \return string
 * \author Achille Cannavale
 * \file file.cpp
 */
string Persona::get_telefono(){
    return telefono;
}

/**
 * \fn istream& operator>>(istream& is, Persona& p)
 * \brief  Operatore di input della classe Persona
 * \return istream
 * \author Achille Cannavale
 * \file file.cpp
 */
istream& operator>>(istream& is, Persona& p){//INPUT
    cout<<"Inserisci le informazioni personali: "<<endl;
    cout<<"Nome: ";
    is>>p.nome;
    cout<<"Cognome: ";
    is>>p.cognome;
    cout<<"Indirizzo: ";
    is>>p.indirizzo;
    cout<<"Telefono: ";
    is>>p.telefono;
    return is;
}

/**
 * \fn ostream& operator<<(ostream& os,   Persona& p)
 * \brief Operatore di output della classe Persona
 * \return ostream
 * \author Achille Cannavale
 * \file file.cpp
 */
ostream& operator<<(ostream& os,   Persona& p){//OUTPUT
    os<<".............Cliente "<<(p.get_cognome())<<" "<<p.get_nome()<<".........."<<endl;
    os<<"Indirizzo: "<<p.get_indirizzo()<<endl;
    os<<"Telefono: "<<p.get_telefono()<<endl;
    os<<"..........................................................."<<endl;
    return os;
}


//** ************** CLIENTE ************** **
/**
 * \fn Cliente::Cliente()
 * \brief Costruttore della classe Cliente
 * \return
 * \author Achille Cannavale
 * \file file.cpp
 */
Cliente::Cliente(){//Costruttore
    Nstanza=0;
    cin>>*this;
}

/**
 * \fn Cliente::Cliente()
 * \brief Costruttore Parametrizzato della classe Cliente
 * \return
 * \author Achille Cannavale
 * \file file.cpp
 */
Cliente::Cliente(string nm, string cg, string ind, string tel, int perm, int num){
    nome=nm;
    cognome=cg;
    indirizzo=ind;
    telefono=tel;
    permanenza=perm;
    Nstanza=num;
}

/**
 * \fn Cliente& Cliente::operator=(const Cliente &cl)
 * \brief Operatore = della classe Cliente
 * \return Cliente
 * \author Achille Cannavale
 * \file file.cpp
 */
Cliente& Cliente::operator=(const Cliente &cl){
    nome=cl.nome;
    cognome=cl.cognome;
    indirizzo=cl.indirizzo;
    permanenza=cl.permanenza;
    Nstanza=cl.Nstanza;
    telefono=cl.telefono;
    return *this;
}

/**
 * \fn istream& operator>>(istream& is, Cliente& c)
 * \brief Operatore di input della classe Cliente
 * \return istream
 * \author Achille Cannavale
 * \file file.cpp
 */
istream& operator>>(istream& is, Cliente& c){
    Persona tmp;
    operator>>(is,tmp);
    c.nome=tmp.get_nome();
    c.cognome=tmp.get_cognome();
    c.indirizzo=tmp.get_indirizzo();
    c.telefono=tmp.get_telefono();
    cout<<"Inserisci la permanenza in giorni: ";
    is>>c.permanenza;
    return is;
}

/**
 * \fn ostream& operator<<(ostream& os,  const Cliente& c)
 * \brief Operatore di output della classe Cliente
 * \return ostream
 * \author Achille Cannavale
 * \file file.cpp
 */
ostream& operator<<(ostream& os,  const Cliente& c){//OUTPUT
    os<<".............Cliente "<<c.cognome<<" "<<c.nome<<".........."<<endl;
    os<<"Numero stanza: "<<c.Nstanza<<endl;
    os<<"Indirizzo: "<<c.indirizzo<<endl;
    os<<"Telefono: "<<c.telefono<<endl;
    os<<"Permanenza: "<<c.permanenza<<endl;
    os<<"..........................................................."<<endl;
    return os;
}


//** ************** DIPENDENTI ************** **
/**
 * \fn Dipendente::Dipendente()
 * \brief Costruttore della classe Dipendente
 * \return Dipendente
 * \author Achille Cannavale
 * \file file.cpp
 */
Dipendente::Dipendente(){
    cin>>*this;
}

/**
 * \fn Dipendente::Dipendente()
 * \brief Costruttore Parametrizzato della classe Dipendente
 * \return Dipendente
 * \author Achille Cannavale
 * \file file.cpp
 */
Dipendente::Dipendente(string nm, string cg, string ind, string tel, int sal, bool temp, string occ){
   nome=nm;
   cognome=cg;
   indirizzo=ind;
   telefono=tel;
   salario=sal;
   tempoIndeterminato=temp;
   occupazione=occ;
}

/**
 * \fn int Dipendente::get_salario(
 * \brief Restituisce il salario del Dipendente
 * \return int
 * \author Achille Cannavale
 * \file file.cpp
 */
int Dipendente::get_salario(){
    return salario;
}

/**
 * \fn string Dipendente::get_occupazione()
 * \brief Restituisce l'occupazione del Dipendente
 * \return string
 * \author Achille Cannavale
 * \file file.cpp
 */
string Dipendente::get_occupazione(){
    return occupazione;
}

/**
 * \fn bool Dipendente::get_tempoIndeterminato()
 * \brief Restituisce se il Dipendente ha un contratto a tempo indeterminato o no
 * \return bool
 * \author Achille Cannavale
 * \file file.cpp
 */
bool Dipendente::get_tempoIndeterminato(){
    return tempoIndeterminato;
}

/**
 * \fn istream& operator>>(istream& is, Dipendente& d)
 * \brief Operatore di input della classe Dipendente
 * \return istream
 * \author Achille Cannavale
 * \file file.cpp
 */
istream& operator>>(istream& is, Dipendente& d){//INPUT
    int check;
    Persona tmp;
    operator>>(is,tmp);
    d.nome=tmp.get_nome();
    d.cognome=tmp.get_cognome();
    d.indirizzo=tmp.get_indirizzo();
    d.telefono=tmp.get_telefono();
    cout<<"Inserisci il salario mensile: ";
    is>>d.salario;
    cout<<"Inserisci l'occupazione: ";
    is>>d.occupazione;
    cout<<"Il dipendente ha un contratto a tempo indeterminato? Y:1 N:0 ";
    is>>check;
    if(check==1){
        d.tempoIndeterminato=true;
    }else{
        d.tempoIndeterminato=false;;
    }
    return is;
}

/**
 * \fn ostream& operator<<(ostream& os,  Dipendente& d)
 * \brief Operatore di output della classe Dipendente
 * \return ostream
 * \author Achille Cannavale
 * \file file.cpp
 */
ostream& operator<<(ostream& os,  Dipendente& d){//OUTPUT
    os<<".............Dipendente "<<d.get_cognome()<<" "<<d.get_nome()<<".........."<<endl;
    os<<"Indirizzo: "<<d.get_indirizzo()<<endl;
    os<<"Telefono: "<<d.get_telefono()<<endl;
    os<<"Salario mensile: "<<d.get_salario()<<endl;
    os<<"Occupazione: "<<d.get_occupazione()<<endl;
    os<<"Tempo indeterminato: "<<d.get_tempoIndeterminato()<<endl;
    os<<"..........................................................."<<endl;
    return os;
}


