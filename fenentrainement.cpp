#include "fenentrainement.h"
#include "ui_fenentrainement.h"
#include "fenedition.h"
#include "ui_fenedition.h"
#include "fenstart.h"
#include "ui_fenstart.h"
#include "timer.h"
#include "sheet.h"
#include "boum.h"
#include <Windows.h>
#include <QKeyEvent>
#include "pa_asio.h"

FenEntrainement::FenEntrainement(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenEntrainement)
{
    ui->setupUi(this);

    QPalette p(palette());
    p.setBrush(QPalette::Window, QBrush(QPixmap(":/images/MesImages/fondEcranEntrainement.jpg")));
    setPalette(p); //Met l'image en fond d'écran

    ui->partition->setFocus();
    Boum *instanceDeBoum = new Boum;
    instanceDeBoum->moveToThread (&threadBoum);
    connect (&threadBoum, &QThread::finished,instanceDeBoum, &QObject::deleteLater);
    connect(this, &FenEntrainement::operate, instanceDeBoum, &Boum::doWork);
    connect(instanceDeBoum, &Boum::resultReady, this, &FenEntrainement::handleResults);
    threadBoum.start();
}

FenEntrainement::~FenEntrainement()
{
    delete ui;
    threadBoum.quit();
    threadBoum.wait();
}

//SLOTS pour passer de page en page
void FenEntrainement::on_boutonRetourMenu_clicked() //Bouton pour revenir à la page d'accueil depuis l'interface d'entraînement
{
    QMessageBox confirmationRetourMenu;
    confirmationRetourMenu.setText(tr("Etes-vous sûr de vouloir retourner à la page d'accueil ?"));
    confirmationRetourMenu.setWindowTitle("DrumMastery");
    QAbstractButton* boutonOui = confirmationRetourMenu.addButton(tr("Oui"), QMessageBox::YesRole);
    confirmationRetourMenu.addButton(tr("Annuler"), QMessageBox::RejectRole);

    confirmationRetourMenu.exec();

    if (confirmationRetourMenu.clickedButton()==boutonOui)
        {
            FenStart *fenetreDemarrage;
            fenetreDemarrage = new FenStart;
            fenetreDemarrage->show();
            this->hide();
         }
}

//SLOTS associés aux clics sur les boutons
void FenEntrainement::on_boutonPlayPause_clicked() //permet de passer du bouton play au bouton pause et inversement
{
    if (!ui->partition->getStarted()) //Si la partition n'est pas lancée, on la lance (copier coller de la partie lancement de "sheet.cpp")
    {
        ui->boutonPlayPause->setStyleSheet("QPushButton{border-image : url(:/images/MesImages/pauseoff.png) 0 0 0 0 stretch stretch; border-width : 0px; background-position : center; min-width : 70px; max-width : 70px; min-height : 70px; max-height : 70px; color : transparent;}");
        this->operate(); //signal qui lance la fonction Boum grâce au connect
        ui->partition->setFocus();
        ui->partition->start();
        //ui->partition->afficherPerformance();
        /*connect ()
        while (ui->partition->getStarted() == true)
        {
            if (QT)
            ui->affichagePerformance->display(ui->partition->getPerformance());
        }*/
    }

    else
    {
        ui->boutonPlayPause->setStyleSheet("QPushButton{border-image : url(:/images/MesImages/playoff.png) 0 0 0 0 stretch stretch; border-width : 0px; background-position : center; min-width : 70px; max-width : 70px; min-height : 70px; max-height : 70px; color : transparent;}");
        ui->partition->stop();
    }
}


void FenEntrainement::on_ouvrirExploreur_clicked() //SLOT pour ouvrir l'exploreur
{
    QStringList listeFichiers = QFileDialog::getOpenFileNames (this, tr("Ouvrir un fichier"), QDir :: currentPath(), tr("Documents (*doc);;All files (*.*)"));
}



void FenEntrainement::on_nouveau_clicked() //pour ouvrir une nouvelle fenêtre d'entraînement
{
    FenEntrainement *nouvelleFenetre;
    nouvelleFenetre = new FenEntrainement;
    nouvelleFenetre->show();
}

void FenEntrainement::on_boutonModeVue_clicked() //Pour activer ou desactiver le mode vue
{
    if (ui->boutonModeVue->text() == "On")
    {
        ui->boutonModeVue->setStyleSheet("QPushButton{border-image : url(:/images/MesImages/vue_off.png) 0 0 0 0 stretch stretch; border-width : 0px; background-position : center; min-width : 70px; max-width : 70px; min-height : 70px; max-height : 70px; color : transparent;}");
        ui->boutonModeVue->setText("Off");
    }

    else
    {
        ui->boutonModeVue->setStyleSheet("QPushButton{border-image : url(:/images/MesImages/vue_on.png) 0 0 0 0 stretch stretch; border-width : 0px; background-position : center; min-width : 70px; max-width : 70px; min-height : 70px; max-height : 70px; color : transparent;}");
        ui->boutonModeVue->setText("On");
    }
}

void FenEntrainement::on_stop_clicked() //pour arrêter la séquence rythmique et la remettre au début
{
    ui->boutonPlayPause->setStyleSheet("QPushButton{border-image : url(:/images/MesImages/playoff.png) 0 0 0 0 stretch stretch; border-width : 0px; background-position : center; min-width : 70px; max-width : 70px; min-height : 70px; max-height : 70px; color : transparent;}");
    ui->boutonPlayPause->setText("Play");
}

void FenEntrainement::on_boutonMetronome_clicked() //Pour activer ou désactiver le métronome
{
    if (ui->boutonMetronome->text() == "On")
    {
        ui->boutonMetronome->setStyleSheet("QPushButton{border-image : url(:/images/MesImages/metronome_off.png) 0 0 0 0 stretch stretch; border-width : 0px; background-position : center; min-width : 70px; max-width : 70px; min-height : 70px; max-height : 70px; color : transparent;}");
        ui->boutonMetronome->setText("Off");
        ui->partition->setMetronome();

    }

    else
    {
        ui->boutonMetronome->setStyleSheet("QPushButton{border-image : url(:/images/MesImages/metronome_on.png) 0 0 0 0 stretch stretch; border-width : 0px; background-position : center; min-width : 70px; max-width : 70px; min-height : 70px; max-height : 70px; color : transparent;}");
        ui->boutonMetronome->setText("On");
        ui->partition->setMetronome();
    }
}

void FenEntrainement::on_boutonVolume_valueChanged(int position)
{
    ui->partition->setKickVolume(position);
    ui->partition->setMetronomeVolume(position);
}

void FenEntrainement::on_boutonSonOn_clicked()
{
    if (ui->boutonSonOn->text() == "son_on")
    {
        ui->boutonSonOn->setStyleSheet("QPushButton{border-width : 0px; background-position : center; min-width : 70px; max-width : 70px; min-height : 70px; max-height : 70px; color : black;}");
        ui->boutonSonOn->setText("son_off");
        ui->boutonVolume->setSliderPosition(0);
    }

    else
    {
        ui->boutonSonOn->setStyleSheet("QPushButton{border-image : url(:/images/MesImages/volume.png) 0 0 0 0 stretch stretch; border-width : 0px; background-position : center; min-width : 70px; max-width : 70px; min-height : 70px; max-height : 70px; color : transparent;}");
        ui->boutonSonOn->setText("son_on");
        ui->boutonVolume->setSliderPosition(99);
    }
}

void FenEntrainement::on_boutonStop_clicked() //pour arrêter la lecture de partition
{
    ui->partition->stop();
    ui->boutonPlayPause->setStyleSheet("QPushButton{border-image : url(:/images/MesImages/playoff.png) 0 0 0 0 stretch stretch; border-width : 0px; background-position : center; min-width : 70px; max-width : 70px; min-height : 70px; max-height : 70px; color : transparent;}");
}

void simulationEspace ()
{
    qDebug("espace simulé");
    //ui->partition->setFocus();
        INPUT simulationAppuiEspace [1];

                        simulationAppuiEspace[0].type = 1; //Pour dire que c'est un keyboard event.
                        simulationAppuiEspace[0].ki.wVk = VK_SPACE;
                        simulationAppuiEspace[0].ki.time = 0;

        INPUT simulationRelacheEspace [1];

                        simulationRelacheEspace[0].type = 1;
                        simulationRelacheEspace[0].ki.wVk = VK_SPACE;
                        simulationRelacheEspace[0].ki.dwFlags = KEYEVENTF_KEYUP;
                        simulationRelacheEspace[0].ki.time = 0;

        SendInput (1,simulationAppuiEspace, sizeof(simulationAppuiEspace));
        SendInput (1,simulationRelacheEspace, sizeof(simulationRelacheEspace));
}

void FenEntrainement::handleResults()
{
    //this->simulationEspace();
}

