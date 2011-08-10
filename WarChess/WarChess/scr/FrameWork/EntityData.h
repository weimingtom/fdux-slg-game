#pragma once

class EntityData
{
public:
	EntityData(QString name)
	{
		this->name=name;
	}

	virtual ~EntityData(){};

	QString name;
	QString GroupName;
	QString EntityType;
};