/// TEMA 2 POO
/// GHADAMIYAN LIDA 212

#include <iostream>
#include <stdlib.h>


using namespace std;


class Complex
{

private:
    float re, im;

public:
    Complex()                                    /// Constructori de init cu si fara param, constr de copiere si destructor
    {
        re = im = 0;
    }
    Complex(float re, float im)
    {
        this->re = re;
        this->im = im;
    }
    Complex(const Complex* c)
    {
        this->re = c->re;
        this->im = c->im;
    }

    ~Complex()
    {

    }

    void set(float re, float im)                 /// setteri si getteri
    {
        this->re = re;
        this->im = im;
    }
    void set(const Complex  c)
    {
        set(c.re, c.im);
    }
    float getRe()
    {
        return re;
    }

    float getIm()
    {
        return im;
    }

    Complex operator + (const Complex c)        ///Operatori pt operatii cu nr complexe
    {
        Complex aux;
        aux.re = this->re + c.re;
        aux.im = this->im + c.im;
        return aux;
    }
    Complex operator - (const Complex c)
    {
        Complex aux;
        aux.re = this->re - c.re;
        aux.im = this->im - c.im;
        return aux;
    }
    Complex operator = (const Complex c)
    {
        this->re = c.re;
        this->im = c.im;
        return *this;
    }

    Complex operator * (Complex c)
    {
        Complex aux;
        aux.re = this->getRe() * c.getRe() - this->getIm()*c.getIm();
        aux.im = this->getIm() * c.getRe() + this->getRe() * c.getIm();
        return aux;
    }
    Complex operator * (int c)
    {
        Complex aux;
        aux.re = this->getRe() * c;
        aux.im = this->getIm() * c;
        return aux;
    }

    friend istream& operator >> (istream& in, Complex& num)  /// Operatorii pt citire si afisare
    {
        in >> num.re;
        in >> num.im;
        return in;
    }
    friend ostream& operator << (ostream& out, const Complex& num)
    {
        if(num.im > 0)
        {
            out << num.re << "+" << num.im<<"i";
        }
        else if(num.im == 0)
        {
            out << num.re;
        }
        else if(num.im < 0)
        {
            out << num.re << "-" << num.im <<"i";
        }
        return out;
    }
};

class Matrice                                                       /// Clasa de baza
{

protected:

    Complex **v;

public:

    virtual  bool diagonal(int linii, int coloane)           /// Functii virtuale
    {
        for(int i = 0; i < linii; i++)
        {
            for(int j = 0; j < coloane; j++)
            {
                if(i != j && v[i][j].getRe() != 0 && v[i][j].getIm() != 0)
                    return false;
            }
        }

        return true;
    }

    virtual bool superior_triunghi(int linii, int coloane)
    {
        for(int i = 0; i < linii; i++)
        {
            for(int j = 0; j < i && j < coloane; j++)
            {
                if( v[i][j].getRe() != 0 && v[i][j].getIm() != 0)
                    return false;
            }
        }

        return true;
    }

    virtual bool inferior_triunghi(int linii, int coloane)
    {
        for(int i = 0; i < linii; i++)
        {
            for(int j = i+1; j < coloane; j++)
            {
                if(v[i][j].getRe() != 0 && v[i][j].getIm() != 0)
                    return false;
            }
        }

        return true;
    }

    virtual void print(int linii, int coloane)
    {
        for(int i = 0; i< linii; i++)
        {
            for(int j = 0; j< coloane; j++)
                cout << v[i][j] << " ";
            cout << endl;
        }

    }

    void init(int linii, int coloane)
    {
        v = new Complex*[linii];

        for(int i = 0; i < linii; i++)
        {
            v[i] = new Complex[coloane]();
        }

    }

    Matrice()                                          /// Constr fara si cu param, constr de copiere si destructor
    {
        v = NULL;
    }

    Matrice(int linii, int coloane)
    {
        init(linii, coloane);
    }

    ~Matrice()
    {
        delete[] v;
    }

    void set(int i, int j, const Complex c)             /// Setter si getter
    {
        v[i][j].set(c);
    }

    Complex get(int i, int j)
    {
        return v[i][j];
    }

    void umple(int n, int m)                           /// Functie care genereaza o matrice cu nr random
    {
        int real, imag;
        Complex aux;
        for (int i = 0; i< n; i++)
            for(int j = 0; j< m; j++)
            {
                real=rand()%10;
                imag=rand()%10;
                aux.set(real, imag);
                v[i][j].set(aux);
            }
    }

    friend istream& operator >> (istream &in, Matrice mat)   /// Operatorii de citire si afisare
    {
        int linii, coloane, real, imaginar;
        Complex aux;
        in >> linii;
        in >> coloane;
        for(int i = 0; i< linii; i++)
            for(int j = 0; j< coloane; j++)
            {
                in >>  real;
                in >> imaginar;
                aux.set(real, imaginar);
                mat.set(i, j, aux);
            }
        return in;
    }

    friend ostream& operator << (ostream &out, Matrice mat)
    {
        int linii, coloane;
        cout << "Introduceti nr de linii si coloane al matricei pe care doriti sa o afisati: ";
        cin >> linii;
        cin >> coloane;
        for(int i = 0; i< linii; i++)
        {
            for(int j = 0; j< coloane; j++)
                out << mat.get(i, j) << " ";
            out << endl;
        }
        return out;
    }

};

class Matrice_oarecare: public Matrice             /// Prima clasa derivata
{

private:
    int lin, col;

public:
    Matrice_oarecare(): Matrice()
    {
    }

    Matrice_oarecare(int lin, int col): Matrice(lin, col)
    {
        this->lin = lin;
        this->col = col;
    }

    ~Matrice_oarecare()
    {
        delete[] v;
    }

    void print()
    {
        for(int i = 0; i < lin; i++)
        {
            for(int j = 0; j < col; j++)
            {
                if(v[i][j].getIm() != 0)
                    cout <<v[i][j].getRe() <<"+"<< v[i][j].getIm()<< "i   ";

                else
                    cout <<v[i][j].getRe() <<"      ";
            }
            cout << "\n";
        }
        cout<< '\n';
    }

    bool verificare()                                 /// Functia de verificare din cerinta
    {
        if(superior_triunghi(lin, col) || inferior_triunghi(lin, col))
            return diagonal(lin, col);
        return false;
    }

    friend istream& operator >> (istream &in, Matrice_oarecare mat)   /// Operatorii de citire si scriere
    {
        int real, imaginar;
        Complex aux;
        for(int i = 0; i < mat.lin; i++)
            for(int j = 0; j < mat.col; j++)
            {
                in >>  real;
                in >> imaginar;
                aux.set(real, imaginar);
                mat.set(i, j, aux);
            }
        return in;
    }

    friend ostream& operator << (ostream &out, Matrice_oarecare mat)
    {
        for(int i = 0; i < mat.lin; i++)
        {
            for(int j = 0; j < mat.col; j++)
                out << mat.get(i, j) << " ";
            out << endl;
        }
        return out;
    }

    Matrice_oarecare& operator = (Matrice_oarecare matrice) /// Operator =
    {
        for(int i = 0; i < matrice.lin; i++)
            for(int j = 0; j < matrice.col; j++)
                v[i][j] = matrice.get(i, j);
        return *this;
    }

};

class Matrice_patratica: public Matrice           /// A doua clasa derivata
{

private:
    int dim;

public:

    bool diagonal()
    {
        for(int i = 0; i < dim; i++)
        {
            for(int j = 0; j < dim; j++)
            {
                if(i != j && v[i][j].getRe() != 0 && v[i][j].getIm() != 0)
                    return false;
            }
        }

        return true;
    }

    bool superior_triunghi()
    {
        for(int i = 0; i < dim; i++)
        {
            for(int j = 0; j < i && j < dim; j++)
            {
                if( v[i][j].getRe() != 0 && v[i][j].getIm() != 0)
                    return false;
            }
        }

        return true;
    }

    bool inferior_triunghi()
    {
        for(int i = 0; i < dim; i++)
        {
            for(int j = i+1; j < dim; j++)
            {
                if(v[i][j].getRe() != 0 && v[i][j].getIm() != 0)
                    return false;
            }
        }

        return true;
    }

    Matrice_patratica(): Matrice()
    {
    }

    Matrice_patratica(int dim): Matrice(dim, dim)
    {
        this->dim = dim;
    }

    ~Matrice_patratica()
    {
        delete[] v;
    }

    void print()                                 /// Functia de afisare contine si determinantul
    {
        for(int i = 0; i < dim; i++)
        {
            for(int j = 0; j < dim; j++)
            {
                if(v[i][j].getIm() != 0)
                    cout <<v[i][j].getRe() <<"+"<< v[i][j].getIm()<< "i   ";

                else
                    cout <<v[i][j].getRe() <<"      ";
            }
            cout << "\n";
        }
        cout<<"\nDeterminant: "<<determinant().getRe()<<"+"<<determinant().getIm()<<"i \n\n";
    }

    bool verificare()                                          /// Functia de verificare din cerinta
    {
        if(superior_triunghi() || inferior_triunghi())
            return
            diagonal();
        return false;
    }

    Complex determinant()                         /// Sursa: https://stackoverflow.com/questions/21220504/matrix-determinant-algorithm-c
    {
        Matrice_patratica Minor(dim - 1);
        int c1,c2;
        Complex determinant;

        int O=1;

        if(dim == 2)
        {
            determinant = v[0][0]*v[1][1]-v[0][1]*v[1][0];
            return determinant;
        }
        else
        {
            for(int i = 0; i < dim; i++)
            {
                c1 = 0, c2 = 0;
                for(int j = 0; j < dim; j++)
                {
                    for(int k = 0; k < dim; k++)
                    {
                        if(j != 0 && k != i)
                        {
                            Minor.set(c1, c2, v[j][k]);
                            c2++;
                            if(c2>dim-2)
                            {
                                c1++;
                                c2=0;
                            }
                        }
                    }
                }
                determinant = determinant + (v[0][i]*Minor.determinant()) *O;
                O=-1*O;
            }
        }
        return determinant;

    }

    friend istream& operator >> (istream &in, Matrice_patratica mat)   /// Operatorii de citire si afisare
    {
        int real, imaginar;
        Complex aux;
        for(int i = 0; i < mat.dim; i++)
            for(int j = 0; j < mat.dim; j++)
            {
                in >>  real;
                in >> imaginar;
                aux.set(real, imaginar);
                mat.set(i, j, aux);
            }
        return in;
    }

    friend ostream& operator << (ostream &out, Matrice_patratica mat)
    {
        for(int i = 0; i < mat.dim; i++)
        {
            for(int j = 0; j < mat.dim; j++)
                out << mat.get(i, j) << " ";
            out << endl;
        }
        return out;
    }

    Matrice_patratica& operator = (Matrice_patratica matrice)        /// Operator =
    {
        for(int i = 0; i < matrice.dim; i++)
            for(int j = 0; j < matrice.dim; j++)
                v[i][j] = matrice.get(i, j);
        return *this;
    }

};

int main()
{

    Matrice a(5, 5), b(5, 5);
    Matrice_oarecare c(5, 5), x(3, 5);
    Matrice_patratica d(3);
    Complex e(2, 1), r(74, 62);
    for(int i  = 0; i < 3; i++)
    {
        d.set(i, i, e);
    }
    for(int i  = 0; i < 3; i++)
        for(int j  = 0; j < 3; j++)
        if (i == j)
            x.set(i, j, r);

    d.print();
    if(d.verificare()) cout<<"\nVerificare!\n\n";
    x.print();
    if(x.verificare()) cout<<"\nVerificare!\n\n";
    c.umple(5, 5);
    c.print();

    return 0;
}
