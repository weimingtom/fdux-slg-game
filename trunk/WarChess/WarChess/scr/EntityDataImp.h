#include "EntityData.h"

class EntityDataImp:public EntityData
{
public:
	EntityDataImp(QString name):EntityData(name),EntityName(""),MatName("")
	{
		
	}

	EntityDataImp(EntityDataImp& data):EntityData(data.name)
	{
		this->EntityName=data.EntityName;
		this->GroupName=data.GroupName;
		this->MatName=data.MatName;
	}

	QString EntityName;
	QString MatName;
};