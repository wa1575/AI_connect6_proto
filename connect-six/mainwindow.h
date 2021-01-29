#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*! \class MainWindow
 *  \brief MainWindow
 */

#include <QMainWindow>
#include "item.h"
#include "board.h"
#include <QString>
#include <QInputDialog>
#include "stdafx.h"

namespace Ui {
	class MainWindow;
}

class Board;
class MainWindow : public QMainWindow
{
    friend class Board;
    Q_OBJECT



public:

    /*!
    *  \fn MainWindow::MainWindow(QWidget *parent = NULL);
    *  \brief 생성자
    *
    *  창을 초기화
    *
    *  \param[in] 부모 세트를 통해 Qt 자체가 부모 클래스를 삭제할 때 객체 할당 해제를 처리합니다.
    *
    *  \fn ~MainWindow()
    *  \brief 소멸자
    */
    explicit MainWindow(char *argv[], const int argc, QWidget *parent = NULL);
	~MainWindow();




public slots:

    /*!
     *  \fn void MainWindow::displayStatus (int)
     *  \brief 게임 내 다양한 ​​이벤트 표시 관리
     *  \param[in] event 이벤트 신호

     *  \fn void MainWindow::setStatusBar (int)
     *  \brief 상태 표시 줄을 사용하여 게임 내 다양한 ​​이벤트 표시 관리
     *  \param[in] event  이벤트 신호

     *  \fn void MainWindow::buttonPressHandle (int)
     *  \brief 창에서 버튼을 비활성화 / 활성화합니다.
     *  \param[in] x 활성화 / 비활성화
     */
	void displayStatus (const int &);
	void setStatusBar (const int&);
	void buttonPressHandle (const int&);

	void ConnectToGame();
    void startNetworkGame();

    void on_textEdit_textChanged();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

private slots:
   // void on_lineEdit_cursorPositionChanged(int arg1, int arg2);





    void on_quitButton_clicked();

private:

    /*!
     *
     *  \var MainWindow::ui
     *  \brief 응용 프로그램 GUI에 대한 포인터
     *
     *  \var MainWindow::array
     *  \brief 동적으로 할당된 경기장에 대한 포인터
     *
     *  \var MainWindow::circle
     *  \brief 이미지에 대한 포인터 (원)
     *
     *  \var MainWindow::cross
     *  \brief 이미지에 대한 포인터 (십자)
     *
     *  \var MainWindow::empty
     *  \brief 이미지에 대한 포인터 (빈 필드)
     *
     */

	Ui::MainWindow *ui;
	Board * array;

	QPixmap *circle;
	QPixmap *cross;
	QPixmap *empty;
    QPixmap *black1;
    QPixmap *white1;
    QPixmap *black2;
    QPixmap *black3;
    QPixmap *white2;
    QPixmap *white3;
    QPixmap *blackcow;
    QPixmap *whitecow;


};

#endif // MAINWINDOW_H
