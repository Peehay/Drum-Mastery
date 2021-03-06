#include <QWidget>
#include <QPainter>
#include <QPixmap>

#include "stdlib.h"
#include "note.h"
#include "measure.h"
#include "notes_jugees.h"
#include "math.h"
#include "colored.h"

Colored::Colored(QWidget *parent, int taille_mesure, Note_jugee* t_liste_jugee[10], Measure *mesure, int vit, int nb_mesure, int dureeTemps, int dureeMesure)
    : QWidget(parent)
{
    vue = true;
    m_taille_mesure = taille_mesure;
    nbre_mesure = nb_mesure;
    int i;
    for(i=0; i<10; i++)
        tab_liste_jugee[i] = t_liste_jugee[i];
    m_mesure = mesure;
    vitesse = vit;
    indice_essai = 1;
    duree1Temps = dureeTemps;
    duree1Mesure = dureeMesure;
}


void Colored::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    /*mesure d'essais*/
    int a;
    if(nbre_mesure == 1)
    {
        for (a=0; a < indice_essai; a++)
        {
            painter.setPen(QPen(QColor(80,80,80,255), 3));
            painter.drawLine(300, 60+a*75, m_taille_mesure + 300, 60+a*75); // barre horizontale
            painter.drawLine(300, 45+a*75, 300, 75+a*75); // barre début mesure
            painter.drawLine(m_taille_mesure + 300, 45+a*75, m_taille_mesure + 300, 75+a*75); // barre fin mesure
            painter.setPen(QPen(QColor(80,80,80,255), 1));
            painter.drawLine(m_taille_mesure/4 + 300, 50+a*75, m_taille_mesure/4 + 300, 70+a*75);// barre de mesure
            painter.drawLine(2*m_taille_mesure/4 + 300, 50+a*75, 2*m_taille_mesure/4 + 300, 70+a*75);// barre de mesure
            painter.drawLine(3*m_taille_mesure/4 + 300, 50+a*75, 3*m_taille_mesure/4 + 300, 70+a*75);// barre de mesure

            QString p;
            p.append(QString("%1").arg(a+1));
            painter.setPen(QPen(Qt::blue, 3));
            QFont font = painter.font();
            font.setPointSize(25);
            painter.setFont(font);
            painter.drawText(265, 70+a*75, p);
        }
    }
    if (nbre_mesure == 2)
    {
        for (a=0; a < indice_essai; a++)
        {
            painter.setPen(QPen(QColor(80,80,80,255), 3));
            painter.drawLine(50, 60+a*75, 2*m_taille_mesure + 50, 60+a*75); // barre horizontale
            painter.drawLine(50, 45+a*75, 50, 75+a*75); // barre début mesure
            painter.drawLine(2*m_taille_mesure + 50, 45+a*75, 2*m_taille_mesure + 50, 75+a*75); // barre fin mesure
            painter.setPen(QPen(QColor(80,80,80,255), 1));

            int i;
            for(i = 0; i < 8; i++)
            {
                if(i == 4)
                {
                    painter.setPen(QPen(QColor(80,80,80,255), 3));
                    painter.drawLine(i*m_taille_mesure/4 + 50, 45+a*75, i*m_taille_mesure/4 + 50, 75+a*75);// barre de mesure
                }
                else
                {
                    painter.setPen(QPen(QColor(80,80,80,255), 1));
                    painter.drawLine(i*m_taille_mesure/4 + 50, 50+a*75, i*m_taille_mesure/4 + 50, 70+a*75);// barre de mesure
                }
            }

            QString p;
            p.append(QString("%1").arg(a+1));
            painter.setPen(QPen(Qt::blue, 3));
            QFont font = painter.font();
            font.setPointSize(25);
            painter.setFont(font);
            painter.drawText(15, 70+a*75, p);
        }
    }
    if(nbre_mesure > 2)
    {
        for (a=0; a < indice_essai; a++)
        {
            painter.setPen(QPen(QColor(80,80,80,255), 3));
            painter.drawLine(50, 60+a*125, 2*m_taille_mesure + 50, 60+a*125); // barre horizontale 1
            painter.drawLine(50, 110+a*125, (nbre_mesure == 4)? 2*m_taille_mesure + 50 : m_taille_mesure + 50, 110+a*125); // barre horizontale 2
            painter.drawLine(50, 45+a*125, 50, 75+a*125); // barre début mesure 1
            painter.drawLine(50, 95+a*125, 50, 125+a*125); // barre début mesure 2
            painter.drawLine(2*m_taille_mesure + 50, 45+a*125, 2*m_taille_mesure + 50, 75+a*125); // barre fin mesure 1
            painter.drawLine((nbre_mesure == 4)? 2*m_taille_mesure + 50 : m_taille_mesure + 50, 95+a*125,(nbre_mesure == 4)? 2*m_taille_mesure + 50 : m_taille_mesure + 50, 125+a*125); // barre fin mesure 2
            painter.setPen(QPen(QColor(80,80,80,255), 1));

            int i;
            for(i = 0; i < 8; i++)
            {
                if(i == 4)
                {
                    painter.setPen(QPen(QColor(80,80,80,255), 3));
                    painter.drawLine(i*m_taille_mesure/4 + 50, 45+a*125, i*m_taille_mesure/4 + 50, 75+a*125);// barres de mesure 1
                    if(nbre_mesure == 4)
                        painter.drawLine(i*m_taille_mesure/4 + 50, 95+a*125, i*m_taille_mesure/4 + 50, 125+a*125);// barres de mesure 2
                }
                else
                {
                    painter.setPen(QPen(QColor(80,80,80,255), 1));
                    painter.drawLine(i*m_taille_mesure/4 + 50, 50+a*125, i*m_taille_mesure/4 + 50, 70+a*125);// barres de mesure 1
                    if(i < 4 || nbre_mesure == 4)
                    painter.drawLine(i*m_taille_mesure/4 + 50, 100+a*125, i*m_taille_mesure/4 + 50, 120+a*125);// barres de mesure 2
                }
            }

            QString p;
            p.append(QString("%1").arg(a+1));
            painter.setPen(QPen(Qt::blue, 3));
            QFont font = painter.font();
            font.setPointSize(25);
            painter.setFont(font);
            if(nbre_mesure <= 2)
                painter.drawText(15, 95+a*75, p);
            else
                painter.drawText(15, 95+a*125, p);
        }
    }

    /*Dessin sur la mesure d'essai*/
    QRectF source(0, 0, 30, 58);
    if(vue && !started && indice_essai >= 10)
    {
        painter.setPen(QPen(Qt::black, 10));
        int a;
        for(a=0; a<indice_essai; a++)
        {
            int x = 53;
            if(nbre_mesure == 1)
                x = 303;
            int j;
            Measure* mesure_int = m_mesure;
            for(j=0; j < nbre_mesure; j++)
            {
                if (j == 2)
                    x = 53;
                if(mesure_int->getNote() != NULL)
                {
                    Note *note_int = mesure_int->getNote(); //note intermédiaire pour parcourir la liste de notes
                    float valeur_prec = note_int->getValeur(); //retient en mémoire la valeur de la note d'avant
                    while (note_int->estDerniere() != true)
                    {
                        note_int = note_int->getSuivante();
                        if(nbre_mesure <= 2)
                            painter.drawPixmap(QRectF(x, (j >= 2)? 58 + a*75 : 8 + a*75, 30, 58), ImageOfNote(note_int, 'g'), source);
                        else
                            painter.drawPixmap(QRectF(x, (j >= 2)? 58 + a*125 : 8 + a*125, 30, 58), ImageOfNote(note_int, 'g'), source);
                        valeur_prec = note_int->getValeur();
                        x += int(valeur_prec*m_taille_mesure);
                    }
                }
                mesure_int = mesure_int->getSuivante();
            }
        }
     }

    /*écriture et coloration des notes jouées sur la mesure d'essais*/
    int c;
    int xn, yn;
    painter.setPen(QPen(Qt::black, 10));
    QPixmap image2;
    QRectF source2(0, 0, 30, 58);

    switch(nbre_mesure) //pas les mêmes affichages selon le nombre de mesures
    {
    case 1 :
        for(c=(indice_essai > 2 && started) ? indice_essai - 2 : 0; c<indice_essai; c++)
        {
            Note_jugee *liste_note = tab_liste_jugee[c];
            while (!liste_note->estDerniere())
            {
                if ((liste_note->getTemps()+vitesse*16 > duree1Mesure*nbre_mesure))
                {
                    xn = 50 + 250 + liste_note->getTemps()*m_taille_mesure/duree1Mesure - m_taille_mesure;
                    //qDebug("temps : %d", liste_note->getTemps());
                    //qDebug("xn : %d\n", xn);
                    yn = 13 + c*75;
                }
                else
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure+50 + 250;
                    //qDebug("temps : %d", liste_note->getTemps());
                    //qDebug("xn : %d\n", xn);
                    yn = 13 + c*75;
                }

                if(liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_v.png");
                if(!liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_r.png");

                if (!liste_note->estDefaut())
                {
                    qDebug("xn : %d, temps : %d, essai : %d", xn, liste_note->getTemps(), c+1);
                    painter.drawPixmap(QRectF(xn, yn, 30, 58), image2, source2);
                }
                liste_note = liste_note->getSuivante();
            }
            if(!liste_note->estDefaut())
            {
                if ((liste_note->getTemps()+vitesse*16 > duree1Mesure*nbre_mesure))
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 + 250 - m_taille_mesure;
                    yn = 13 + c*75;
                }
                else
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 + 250;
                    yn = 13 + c*75;
                }

                if(liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_v.png");
                if(!liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_r.png");

                if (!((liste_note->getTemps() == 0) && (liste_note->getSuivante() == NULL) && (liste_note->getCorrecte() == false)))
                {
                    //qDebug("xn : %d, temps : %d, essai : %d", xn, liste_note->getTemps(), c+1);
                    painter.drawPixmap(QRectF(xn, yn, 30, 58), image2, source2); //dessin de la derniere note jugee
                }
            }
        }
        break;

    case 2 :
        for(c=(indice_essai > 2 && started) ? indice_essai - 2 : 0; c<indice_essai; c++)
        {
            Note_jugee *liste_note = tab_liste_jugee[c];
            while (!liste_note->estDerniere())
            {
                if(c == 0 && liste_note == getNoteJugee(1, tab_liste_jugee[0]) && liste_note->getTemps()+vitesse*16 > duree1Mesure)
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - m_taille_mesure;
                    yn = 13 + c*75;
                }
                else if ((liste_note->getTemps()+vitesse*16 > duree1Mesure*nbre_mesure))
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - 2*m_taille_mesure;
                    yn = 13 + c*75;
                }
                else
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50;
                    yn = 13 + c*75;
                }

                if(liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_v.png");
                if(!liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_r.png");

                if (!((liste_note->getTemps() == 0) && (liste_note->getSuivante() == NULL) && (liste_note->getCorrecte() == false)))
                {
                    painter.drawPixmap(QRectF(xn, yn, 30, 58), image2, source2);
                }
                liste_note = liste_note->getSuivante();
            }
            if(!liste_note->estDefaut())
            {
                if(liste_note == getNoteJugee(1, tab_liste_jugee[0]) && liste_note->getTemps()+vitesse*16 > duree1Mesure)
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - m_taille_mesure;
                    yn = 13 + c*75;
                }
                else if ((liste_note->getTemps()+vitesse*16 > duree1Mesure*nbre_mesure))
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - 2*m_taille_mesure;
                    yn = 13 + c*75;
                }
                else
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50;
                    yn = 13 + c*75;
                }

                if(liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_v.png");
                if(!liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_r.png");

                if (!((liste_note->getTemps() == 0) && (liste_note->getSuivante() == NULL) && (liste_note->getCorrecte() == false)))
                {
                    painter.drawPixmap(QRectF(xn, yn, 30, 58), image2, source2); //dessin de la derniere note jugee
                }
            }
        }
        break;

    case 3 :
        for(c=(indice_essai > 2 && started) ? indice_essai - 2 : 0; c<indice_essai; c++)
        {
            Note_jugee *liste_note = tab_liste_jugee[c];
            while (!liste_note->estDerniere())
            {
                if(liste_note == getNoteJugee(1, tab_liste_jugee[0]) && liste_note->getTemps()+vitesse*16 > duree1Mesure)
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - m_taille_mesure;
                    yn = 13 + c*125;
                }
                else if ((liste_note->getTemps()+vitesse*16 > duree1Mesure*nbre_mesure))
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - 3*m_taille_mesure;
                    yn = 13 + c*125;
                }
                else
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50;
                    yn = 13 + c*125;
                    if(xn > 2*m_taille_mesure)
                    {
                        xn = xn - 2*m_taille_mesure;
                        yn = yn + 50;
                    }
                }

                if(liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_v.png");
                if(!liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_r.png");

                if (!((liste_note->getTemps() == 0) && (liste_note->getSuivante() == NULL) && (liste_note->getCorrecte() == false)))
                {
                    //qDebug("xn : %d, yn : %d, temps : %d", xn, yn, liste_note->getTemps());
                    painter.drawPixmap(QRectF(xn, yn, 30, 58), image2, source2);
                }
                liste_note = liste_note->getSuivante();
            }
            if(!liste_note->estDefaut())
            {
                if(liste_note == getNoteJugee(1, tab_liste_jugee[c]) && liste_note->getTemps()+vitesse*16 > duree1Mesure)
                {
                    if(c == 0)
                        xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - m_taille_mesure;
                    else
                        xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - 3* m_taille_mesure;
                    yn = 13 + c*125;
                }
                else if ((liste_note->getTemps()+vitesse*16 > duree1Mesure*nbre_mesure))
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - 2*m_taille_mesure;
                    yn = 13 + c*125;
                }
                else
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50;
                    yn = 13 + c*125;
                    if(xn > 2*m_taille_mesure)
                    {
                        xn = xn - 2*m_taille_mesure;
                        yn = yn + 50;
                    }
                }

                if(liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_v.png");
                if(!liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_r.png");

                if (!((liste_note->getTemps() == 0) && (liste_note->getSuivante() == NULL) && (liste_note->getCorrecte() == false)))
                {
                    //qDebug("xn : %d, temps : %d", xn, liste_note->getTemps());
                    painter.drawPixmap(QRectF(xn, yn, 30, 58), image2, source2); //dessin de la derniere note jugee
                }
            }
        }
        break;

    case 4 :
        for(c=(indice_essai > 2 && started) ? indice_essai - 2 : 0; c<indice_essai; c++)
        {
            Note_jugee *liste_note = tab_liste_jugee[c];
            while (!liste_note->estDerniere())
            {
                if(liste_note == getNoteJugee(1, tab_liste_jugee[0]) && liste_note->getTemps()+vitesse*16 > duree1Mesure)
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - m_taille_mesure;
                    yn = 13 + c*125;
                }
                else if ((liste_note->getTemps()+vitesse*16 > duree1Mesure*nbre_mesure))
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - 4*m_taille_mesure;
                    yn = 13 + c*125;
                }
                else
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50;
                    yn = 13 + c*125;
                    if(xn > 2*m_taille_mesure)
                    {
                        xn = xn - 2*m_taille_mesure;
                        yn = yn + 50;
                    }
                }

                if(liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_v.png");
                if(!liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_r.png");

                if (!((liste_note->getTemps() == 0) && (liste_note->getSuivante() == NULL) && (liste_note->getCorrecte() == false)))
                {
                    //qDebug("xn : %d, temps : %d", xn, liste_note->getTemps());
                    painter.drawPixmap(QRectF(xn, yn, 30, 58), image2, source2);
                }
                liste_note = liste_note->getSuivante();
            }
            if(!liste_note->estDefaut())
            {
                if(liste_note == getNoteJugee(1, tab_liste_jugee[c]) && liste_note->getTemps()+vitesse*16 > duree1Mesure)
                {
                    if(c == 0)
                        xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - m_taille_mesure;
                    else
                        xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - 4*m_taille_mesure;
                    yn = 13 + c*125;
                }
                else if ((liste_note->getTemps()+vitesse*16 > duree1Mesure*nbre_mesure))
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50 - 4*m_taille_mesure;
                    yn = 13 + c*125;
                }
                else
                {
                    xn = liste_note->getTemps()*m_taille_mesure/duree1Mesure + 50;
                    yn = 13 + c*125;
                    if(xn > 2*m_taille_mesure)
                    {
                        xn = xn - 2*m_taille_mesure;
                        yn = yn + 50;
                    }
                }

                if(liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_v.png");
                if(!liste_note->getCorrecte())
                    image2.load(":/notes/MesNotes/noire_r.png");

                if (!((liste_note->getTemps() == 0) && (liste_note->getSuivante() == NULL) && (liste_note->getCorrecte() == false)))
                {
                    //qDebug("xn : %d, temps : %d", xn, liste_note->getTemps());
                    painter.drawPixmap(QRectF(xn, yn, 30, 58), image2, source2); //dessin de la derniere note jugee
                }
            }
        }
        break;

    default :
        break;
    }
}

QPixmap Colored::ImageOfNote(Note *note, char c)
{
    double i = note->getValeur();
    QPixmap pix;
    if(c == 'n')
    {
        if (i == 1.0)
            pix.load(":/notes/MesNotes/ronde_n.png");
        if (i == 0.5)
            pix.load(":/notes/MesNotes/blanche_n.png");
        if (i == 0.25)
            pix.load(":/notes/MesNotes/noire_n.png");
        if (i == 0.125)
            pix.load(":/notes/MesNotes/croche_n.png");
        if (i == 0.0625)
            pix.load(":/notes/MesNotes/double_croche_n.png");
        if (i == 0.03125)
            pix.load(":/notes/MesNotes/triple_croche_n.png");
    }
    if(c == 'g')
    {
        if (i == 1.0)
            pix.load(":/notes/MesNotes/ronde_g.png");
        if (i == 0.5)
            pix.load(":/notes/MesNotes/blanche_g.png");
        if (i == 0.25)
            pix.load(":/notes/MesNotes/noire_g.png");
        if (i == 0.125)
            pix.load(":/notes/MesNotes/croche_g.png");
        if (i == 0.0625)
            pix.load(":/notes/MesNotes/double_croche_g.png");
        if (i == 0.03125)
            pix.load(":/notes/MesNotes/triple_croche_g.png");
    }

    return pix;
}

void Colored::setIndice_essai(int indice)
{
    indice_essai = indice;
}

void Colored::setStarted(bool v)
{
    started = v;
}

void Colored::setDecompte(bool d)
{
    decompte = d;
}

int Colored::getIndice_essai()
{
    return indice_essai;
}

void Colored::setNbMesure(int nb)
{
    nbre_mesure = nb;
}

Note_jugee* Colored::getNoteJugee(int numero, Note_jugee* premiere_note)
{
    if(numero == 1)
        return premiere_note;
    else
    {
        int i;
        Note_jugee* note_int = premiere_note;
        for (i=1; i < numero; i++)
        {
            note_int = note_int->getSuivante();
        }
        return note_int;
    }
}

void Colored::setTabListesJugees(Note_jugee* t_liste_jugee[])
{
    int i;
    for(i=0; i<indice_essai; i++)
        tab_liste_jugee[i] = t_liste_jugee[i];
}

void Colored::setDuree1Mesure(int bpm)
{
    duree1Mesure = 4 * 60*1000/bpm;
}
