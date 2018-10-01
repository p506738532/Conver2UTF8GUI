#include "matlabComboboxDelegate.h"
#include <QComboBox>
namespace WEE{
	MatlabComBoxDelegate::MatlabComBoxDelegate(QObject *parent)
		: QItemDelegate(parent)
	{
	}

	//创建组合框，初始化内容	
	QWidget *MatlabComBoxDelegate::createEditor(QWidget *parent,
		const QStyleOptionViewItem &/* option */,
		const QModelIndex &/* index */) const
	{
		QComboBox *editor = new QComboBox(parent);
		editor->addItems(itemStringList);
		editor->setCurrentIndex(0);
		return editor;
	}

	void MatlabComBoxDelegate::setEditorData(QWidget *editor,
		const QModelIndex &index) const
	{
		QString str = (index.model()->data(index, Qt::EditRole).toString());
		//int value =  (index.model()->data(index, Qt::EditRole).toInt());
		QComboBox *comBox = static_cast<QComboBox*>(editor);
		int i = itemStringList.indexOf(str);
		comBox->setCurrentIndex(i);
	}

	void MatlabComBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
		const QModelIndex &index) const
	{
		QComboBox *comBox = static_cast<QComboBox*>(editor);
		QString score = comBox->currentText();
		model->setData(index, score, Qt::EditRole);
	}


	void MatlabComBoxDelegate::updateEditorGeometry(QWidget *editor,
		const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
	{
		editor->setGeometry(option.rect);
	}
}