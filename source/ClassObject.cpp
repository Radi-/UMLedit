
#include "header/ClassObject.h"

ClassObject::ClassObject(){

    stringPropertyManager.reset(new QtStringPropertyManager());
    fontPropertyManager.reset(new QtFontPropertyManager());

    nameFont = fontPropertyManager.data()->addProperty("Name");
    textFont = fontPropertyManager.data()->addProperty("Attributes and methods");
    name = stringPropertyManager.data()->addProperty("Name");
    classGroup = groupPropertyManager.data()->addProperty("Class");
    fontGroup = groupPropertyManager.data()->addProperty("Font");

    fontGroup->addSubProperty(nameFont);
    fontGroup->addSubProperty(textFont);

    classGroup->addSubProperty(name);
    classGroup->addSubProperty(fontGroup);

    lineEditFactory.reset(new QtLineEditFactory());
    fontFactory.reset(new QtFontEditorFactory());

    propertyBrowser.data()->setFactoryForManager(stringPropertyManager.data(), lineEditFactory.data());
    propertyBrowser.data()->setFactoryForManager(fontPropertyManager.data(), fontFactory.data());
    propertyBrowser.data()->addProperty(classGroup);

    QPoint size(200, 150);
    pointPropertyManager.data()->setValue(sizep, size);
    colorPropertyManager.data()->setValue(this->colour, QColor(200, 200, 200, 255));
    stringPropertyManager.data()->setValue(name, "class name");

    attributes.push_back("attribute 1");
    attributes.push_back("attribute 2");
    attributes.push_back("attribute 3");
    methods.push_back("method 1");
    methods.push_back("method 2");
    methods.push_back("method 3");
    fontPropertyManager.data()->setValue(nameFont, QFont("Sans", 10, QFont::Bold));
    fontPropertyManager.data()->setValue(textFont, QFont("Sans", 10));
    paddingCoefficient = 0.2;

    connect(stringPropertyManager.data(), SIGNAL(valueChanged(QtProperty*,QString)), this, SLOT(stringPropertyUpdated(QtProperty*,QString)));
    connect(fontPropertyManager.data(), SIGNAL(valueChanged(QtProperty*,QFont)), this, SLOT(stringPropertyUpdated(QtProperty*,QString)));

    updateDrawingParameters();
    setSize(size);
}

ClassObject::~ClassObject(){

}

void ClassObject::stringPropertyUpdated(QtProperty* property, QString string){
    Q_UNUSED(property)
    Q_UNUSED(string)
    updateDrawingParameters();
    setSize(pointPropertyManager->value(this->size));
    update();
}

void ClassObject::setSize(QPoint size){

    //enforce minimum size of the element so that all text fits inside it
    if(size.y() < bottomLineY) size.setY(bottomLineY);
    if(size.x() < edgeLineX) size.setX(edgeLineX);
    Object::setSize(size);
}

void ClassObject::updateDrawingParameters(){

    namePadding = QFontMetrics(fontPropertyManager.data()->value(nameFont)).height() * paddingCoefficient;
    textPadding = QFontMetrics(fontPropertyManager.data()->value(textFont)).height() * paddingCoefficient;

    separatorLine1Y = QFontMetrics(fontPropertyManager.data()->value(nameFont)).height() + 2 * namePadding;
    separatorLine2Y = separatorLine1Y + (QFontMetrics(fontPropertyManager.data()->value(textFont)).height() + 2 * textPadding) * attributes.length();

    bottomLineY = separatorLine2Y + (QFontMetrics(fontPropertyManager.data()->value(textFont)).height() + 2 * textPadding) * methods.length();

    edgeLineX = pointPropertyManager->value(sizep).x();
    int compareWidth = QFontMetrics(fontPropertyManager.data()->value(nameFont)).width(stringPropertyManager->value(name)) + 2 * namePadding;
    if(compareWidth > edgeLineX) edgeLineX = compareWidth;

    for(int i = 0; i < attributes.length(); i++){
        compareWidth = QFontMetrics(fontPropertyManager.data()->value(textFont)).width(attributes.at(i)) + 2 * textPadding;
        if(compareWidth > edgeLineX) edgeLineX = compareWidth;
    }

    for(int i = 0; i < methods.length(); i++){
        compareWidth = QFontMetrics(fontPropertyManager.data()->value(textFont)).width(methods.at(i)) + 2 * textPadding;
        if(compareWidth > edgeLineX) edgeLineX = compareWidth;
    }

}

void ClassObject::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){

    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(colorPropertyManager->value(colour));
    painter->drawRect(0, 0, pointPropertyManager->value(size).x(), pointPropertyManager->value(size).y());
    painter->drawLine(0, separatorLine1Y, pointPropertyManager->value(size).x(), separatorLine1Y);
    painter->drawLine(0, separatorLine2Y, pointPropertyManager->value(size).x(), separatorLine2Y);

    painter->setFont(fontPropertyManager.data()->value(nameFont));
    painter->drawText((pointPropertyManager->value(size).x() - painter->fontMetrics().width(stringPropertyManager->value(name))) * 0.5,
                      QFontMetrics(fontPropertyManager.data()->value(nameFont)).ascent() + namePadding,
                      stringPropertyManager->value(name));

    painter->setFont(fontPropertyManager.data()->value(textFont));
    for(int i = 0; i < attributes.length(); i++){
        painter->drawText(textPadding,
                          separatorLine1Y + (i + 1) * (QFontMetrics(fontPropertyManager.data()->value(textFont)).ascent() + textPadding) + i * (QFontMetrics(fontPropertyManager.data()->value(textFont)).descent() + textPadding),
                          attributes.at(i));
    }

    for(int i = 0; i < methods.length(); i++){
        painter->drawText(textPadding,
                          separatorLine2Y + (i + 1) * (QFontMetrics(fontPropertyManager.data()->value(textFont)).ascent() + textPadding) + i * (QFontMetrics(fontPropertyManager.data()->value(textFont)).descent() + textPadding),
                          methods.at(i));
    }
}

QtTreePropertyBrowser* ClassObject::getPropertyBrowser(){
    return propertyBrowser.data();
}
