#ifndef ITEM_H
#define ITEM_H

/*! \class Item
 *  \brief Item
 *
 *  게임판 생성
 */

#include <QLabel>

//미리 선언
class Board;

class Item : public QLabel
{
	friend class Board;
    Q_OBJECT //오브젝트 선언
public:

	/*!
	*  \enum Type
    *  \brief 필드 TYPE
	*
    *  공백 / 십자 / 원
	*
	*  \fn Item::Item(int y, int x, Board *parent = NULL)
    *  \brief 생성자
	*
    *  하나의 필드를 초기화하고 필요한 변수를 설정합니다.
	*
    *  \param[in] y 필드의 좌표입니다.
    *  \param[in] x je 필드의 좌표입니다.
    *  \param[in] 부모 세트를 통해 Qt 자체가 부모 클래스를 삭제할 때 객체 할당 해제를 처리합니다.
	*/

	enum Type{
		TYPE_EMPTY=0,
		TYPE_CIRCLE=1,
		TYPE_CROSS=2
	};

	explicit Item (const int &, const int &, QPixmap *, Board *parent = NULL);

signals:
public slots:
private:

	/*!
	 *  \fn Item::mousePressEvent (QMouseEvent *)
     *  \brief 마우스 클릭을 캡처하는 오버로드 방법
     *  \param[in] Stisk 상자 위에 마우스 버튼을 누르십시오.
	 *
	 *  \fn Item::clear (void)
     *  \brief 필드 재설정
	 *
	 *  \var Item::x, Item::y
     *  \brief 각 필드의 간략한 X 및 Y 좌표
	 *
	 *  \var Item::type
     *  \brief 필드 유형
     *  - 빈 영역
     *  - 원 영역
     *  - 십자 영역
	 *
	 *  \var Item::parentPtr
     *  \brief 부모에 대한 포인터
	 *
	 *  \var Item::empty
     *  \brief 이미지에 대한 간단한 포인터 (빈 상자)
	 *
	 */

	void mousePressEvent (QMouseEvent *);
	void clear (void);

	int x,y;
	Type type;
	Board* parentPtr;
	QPixmap * empty;
	

};

#endif // ITEM_H
