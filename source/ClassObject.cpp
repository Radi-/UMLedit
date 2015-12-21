
#include "header/ClassObject.h"

ClassObject::ClassObject(){
}

ClassObject::ClassObject(QPoint size, QColor colour){

    this->size = size;
    this->colour = colour;
    name = "class name";
    attributes.push_back("attribute 1");
    attributes.push_back("attribute 2");
    attributes.push_back("attribute 3");
    methods.push_back("method 1");
    methods.push_back("method 2");
    methods.push_back("method 3");
    nameFont = QFont("Sans", 10, QFont::Bold);
    textFont = QFont("Sans", 10);
}

ClassObject::~ClassObject(){
}

void ClassObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){

    const int nameFontHeight = QFontMetrics(nameFont).xHeight();
    const int textFontHeight = QFontMetrics(textFont).xHeight();
    const float textOffsetCoefficient = 1.2;
    const int firstLineY = nameFontHeight * (1.0 + textOffsetCoefficient * 2);
    const int secondLineY = firstLineY +
                            (textFontHeight * (1.0 + textOffsetCoefficient)) * attributes.length() +
                             textFontHeight * textOffsetCoefficient;

    painter->setBrush(colour);
    painter->drawRect(0, 0, size.x(), size.y());
    painter->drawLine(0, firstLineY, size.x(), firstLineY);
    painter->drawLine(0, secondLineY, size.x(), secondLineY);

    painter->setFont(nameFont);
    painter->drawText((size.x() - painter->fontMetrics().width(name)) * 0.5,
                      nameFontHeight * (1.0 + textOffsetCoefficient),
                      name);

    painter->setFont(textFont);
    for(unsigned int i = 0; i < attributes.length(); i++){
        painter->drawText(textFontHeight * textOffsetCoefficient,
                          firstLineY + (i + 1) * textFontHeight * (1.0 + textOffsetCoefficient),
                          attributes.at(i));
    }

    for(unsigned int i = 0; i < methods.length(); i++){
        painter->drawText(textFontHeight * textOffsetCoefficient,
                          secondLineY + (i + 1) * textFontHeight * (1.0 + textOffsetCoefficient),
                          methods.at(i));
    }
}
