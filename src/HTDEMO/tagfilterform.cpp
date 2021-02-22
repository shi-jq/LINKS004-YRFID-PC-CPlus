#include "tagfilterform.h"
#include "ui_tagfilterform.h"
#include "LanguageSrc.h"
#include "appconfig.h"
#include "mainapp.h"
#include "RFIDAPIEXPORT.h"
#include "readerdllbase.h"

TagFilterForm::TagFilterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagFilterForm)
{
    ui->setupUi(this);
	mTagEdit = ui->lineEdit;
	mFilterBtn = ui->pushButton;
	mClearFilterBtn = ui->pushButton_2;

	connect( mFilterBtn, SIGNAL( clicked()), this, SLOT( slot_filterBtnClicked( ) ) );
	connect( mClearFilterBtn, SIGNAL( clicked()), this, SLOT( slot_ClearFilterBtnClicked( ) ) );
}

TagFilterForm::~TagFilterForm()
{
    delete ui;
}

void TagFilterForm::SetTagID(const QString& tagStr)
{
	mTagEdit->setText(tagStr);
}

void TagFilterForm::slot_filterBtnClicked()
{
	
}

void TagFilterForm::slot_ClearFilterBtnClicked()
{
	
}
