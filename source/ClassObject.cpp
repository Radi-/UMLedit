
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

    const int nameFontHeight = QFontMetrics(nameFont).height();
    const int textFontHeight = QFontMetrics(textFont).height();

    const float paddingCoefficient = 0.2;
    const int namePadding = nameFontHeight * paddingCoefficient;
    const int textPadding = textFontHeight * paddingCoefficient;

    const int firstLineY = nameFontHeight + 2 * namePadding;
    const int secondLineY = firstLineY + (textFontHeight + 2 * textPadding) * attributes.length();

    painter->setBrush(colour);
    painter->drawRect(0, 0, size.x(), size.y());
    painter->drawLine(0, firstLineY, size.x(), firstLineY);
    painter->drawLine(0, secondLineY, size.x(), secondLineY);

    painter->setFont(nameFont);
    painter->drawText((size.x() - painter->fontMetrics().width(name)) * 0.5,
                      QFontMetrics(nameFont).ascent() + namePadding,
                      name);

    painter->setFont(textFont);
    for(int i = 0; i < attributes.length(); i++){
        painter->drawText(textPadding,
                          firstLineY + (i + 1) * (QFontMetrics(textFont).ascent() + textPadding) + i * (QFontMetrics(textFont).descent() + textPadding),
                          attributes.at(i));
    }

    for(int i = 0; i < methods.length(); i++){
        painter->drawText(textPadding,
                          secondLineY + (i + 1) * (QFontMetrics(textFont).ascent() + textPadding) + i * (QFontMetrics(textFont).descent() + textPadding),
                          methods.at(i));
    }
}
