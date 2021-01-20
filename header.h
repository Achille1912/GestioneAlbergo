#include <iostream>
#include <string.h>
using namespace std;

int o=0; //Numero progressivo delle stanze

/**
 * \class Persona
 * \brief Questa classe definisce l'entità persona che farà poi da base per Cliente e Dipendente
 * \author Achille Cannavale
 */
class Persona{
   protected:
        string nome, cognome, indirizzo, telefono;
   public:
        Persona();
        string get_nome();
        string get_cognome();
        string get_indirizzo();
        string get_telefono();
        void set_nome(string nm){nome=nm; return;}
        void set_cognome(string cg){cognome=cg; return;}
        void set_indirizzo(string ind){indirizzo=ind; return;}
        void set_telefono(string tel){telefono=tel; return;}
        friend istream& operator>>(istream& is, Persona& p);
};

/**
 * \class Cliente
 * \brief Questa classe definisce l'entità Cliente, derivata da Persona 
 * \author Achille Cannavale
 */
class Cliente:public Persona{
    private:
      int permanenza;
      int Nstanza;
    public:
      Cliente();
      Cliente(string nm, string cg, string ind, string tel, int perm, int num);
      int get_permanenza(){ return permanenza;}
      int get_Nstanza(){ return Nstanza;}
      void set_Nstanza(int n){ Nstanza=n; return;}
      void set_permanenza(int perm){permanenza=perm; return;}
      Cliente& operator=(const Cliente &cl);
      friend istream& operator>>(istream& is, Cliente& c);
      friend ostream& operator<<(ostream& os,  const Cliente& c);
};

/**
 * \class Dipendente
 * \brief Questa classe definisce l'entità Dipendente, derivata da Persona 
 * \author Achille Cannavale
 */
class Dipendente:public Persona{
    private:
        int salario;
        bool tempoIndeterminato;
        string occupazione;
    public:
        Dipendente();
        Dipendente(string nm, string cg, string ind, string tel, int sal, bool temp, string occ);
        int get_salario();
        bool get_tempoIndeterminato();
        string get_occupazione();
        friend istream& operator>>(istream& is, Dipendente& d);
        friend ostream& operator<<(ostream& os,   Dipendente& d);
};

/**
 * \class Stanza
 * \brief Questa classe definisce l'entità Stanza, le cui istanze sranno puntate da un vettore nell'istanza Albergo 
 * \author Achille Cannavale
 */
class Stanza{
    private:
        int piano;
        int numero;
        int Nletti;
        int occupanti;
        int prezzo;
    public:
        Cliente **c;
        Stanza();
        Stanza(int p, int nS, int nL, int pr, int occ);
        int get_piano(){return piano;};
        int get_numero(){return numero;};
        int get_Nletti(){return Nletti;};
        int get_occupanti(){return occupanti;};
        int get_prezzo(){return prezzo;};
        void set_occupanti(int occ){occupanti=occ; return;}
        friend istream& operator>>(istream& is, Stanza& s);
        friend ostream& operator<<(ostream& os,  const Stanza& s);
};



/**
 * \class Albergo
 * \brief Questa classe definisce l'entità Albergo, ed è la classe principale del proggetto
 * \author Achille Cannavale
 */
class Albergo{ 
    private:
        string denominazione;
        string stelle;
        string luogo;
        int Nstanze;
        int Ndipendenti;
        Stanza **v;
        Dipendente **d;
     public:
        Albergo();
        Albergo(string den, string star, string place, int room, int dip);
        void carica(int &tmp);
        void salva();
        bool full();
        bool empty();
        void show_stanze();
        void stanze_occupate();
        void add_cliente();
        int Nclienti();
        void delete_cliente(string nm, string cg);
        void show_clienti(int ordine);
        void emettiFile(ofstream &of,string nm,string cg, int i, int j);
        void add_dipendente();
        void delete_dipendente();
        void show_dipendenti(int ordine);
        bool Dempty();
        friend istream& operator>>(istream& is, Albergo& a);
        friend ostream& operator<<(ostream& os,  const Albergo& a);
};



