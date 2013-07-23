#include<iostream>
#include <libdrizzle-5.1/libdrizzle.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include<string.h>
#include"table_map_event.h"
#include"constants.h"

using namespace std;
using namespace binlogevent;




uint32_t TableMapEvent::getByte4(int pos,const unsigned char* data)
{
	uint32_t tmpMask = mask(32); // all 32 bits set to 1		

	tmpMask=(uint32_t)(data[pos]&tmpMask);
	tmpMask=(uint32_t)(data[pos+1]<<8|tmpMask);
	tmpMask=(uint32_t)(data[pos+2]<<16|tmpMask);
	tmpMask=(uint32_t)(data[pos+3]<<24|tmpMask);
	
	return tmpMask;
}

uint32_t TableMapEvent::getByte3(int pos,const unsigned char* data)
{
	uint32_t tmpMask = mask(32); // all 32 bits set to 1		

	tmpMask=(uint32_t)(data[pos]&tmpMask);
	tmpMask=(uint32_t)(data[pos+1]<<8|tmpMask);
	tmpMask=(uint32_t)(data[pos+2]<<16|tmpMask);
	
	return tmpMask;
}

uint16_t TableMapEvent::getByte2(int pos,const unsigned char* data)
{
	uint16_t tmpMask = mask(16); // all 16 bits set to 1		

	tmpMask=(uint16_t)(data[pos]&tmpMask);
	tmpMask=(uint16_t)(data[pos+1]<<8|tmpMask);

	return tmpMask;
}


uint64_t TableMapEvent::getByte6(int pos,const unsigned char* data)
{
	uint64_t tmpMask = mask(64); // all 64 bits set to 1		

	tmpMask=(uint64_t)(data[pos]&tmpMask);
	tmpMask=(uint64_t)(data[pos+1]<<8|tmpMask);
	tmpMask=(uint64_t)(data[pos+2]<<16|tmpMask);
	tmpMask=(uint64_t)(data[pos+3]<<24|tmpMask);
	tmpMask=(uint64_t)(data[pos+4]<<32|tmpMask);
	tmpMask=(uint64_t)(data[pos+5]<<40|tmpMask);

	return tmpMask;
}

uint64_t TableMapEvent::getByte8(int pos,const unsigned char* data)
{
	uint64_t tmpMask = mask(64); // all 64 bits set to 1		

	tmpMask=(uint64_t)(data[pos]&tmpMask);
	tmpMask=(uint64_t)(data[pos+1]<<8|tmpMask);
	tmpMask=(uint64_t)(data[pos+2]<<16|tmpMask);
	tmpMask=(uint64_t)(data[pos+3]<<24|tmpMask);
	tmpMask=(uint64_t)(data[pos+4]<<32|tmpMask);
	tmpMask=(uint64_t)(data[pos+5]<<40|tmpMask);
	tmpMask=(uint64_t)(data[pos+5]<<48|tmpMask);
	tmpMask=(uint64_t)(data[pos+5]<<56|tmpMask);

	return tmpMask;
}

char * getString(int pos,int len,const unsigned char * data)
{
	char *tmp = (char *)malloc(sizeof(char)*(len));
	int i;
	for(i=pos;i<pos+len;i++)
	{
		tmp[i-pos]=data[i];
	}
	tmp[i-pos]='\0';
	return tmp;
}


void TableMapEvent::initWithData(const unsigned char* data)
{
	int start_pos = 0;  
        setTimestamp(getByte4(start_pos,data));
	start_pos+=4; // 4 byte for timestamp.
	setType((uint8_t)data[start_pos]);
	start_pos+=1; // 1 byte for type of evnet.
	setServerId(getByte4(start_pos,data));
	// from 9 to 12 event size .
	start_pos+=4; // 4 byte of server ID.
	start_pos+=4; // SKIPPED 4 byte for event size.
	setLogPos(getByte4(start_pos,data));
	start_pos+=4;// 4 byte for getting possion of next event.
	setFlagH(getByte2(start_pos,data));
	start_pos+=2;// 2 byte of Binlog event flag.
	setTableId(getByte6(start_pos,data));
	start_pos+=6;// 6 byte for table id.
	setFlagPh(getByte2(start_pos,data));
	start_pos+=2;// 2 byte for post-header flag.
	setSchemaNameLen((uint8_t)data[start_pos]);
	start_pos+=1;// 1 byte for schema name length.
	setSchemaName(getString(start_pos,schema_name_len,data));
	start_pos+= schema_name_len; //schema_name_len byte for schema name.
	//  data[start_pos+getSchemaNameLen()] is Null
	start_pos+=1; //  +1 for Null.
	setTableNameLen((uint8_t)data[start_pos]);
	start_pos+=1;// 1 byte for table name length.
	setTableName(getString(start_pos,table_name_len,data));
	start_pos+=table_name_len+1; // +1 for null
	int colBytes = bytes_col_count((uint32_t)data[start_pos]);
	switch(colBytes)
	{
		case 1:
			setColumnCount((uint64_t)data[start_pos]);
			break;

		case 2:
			setColumnCount((uint64_t)getByte2(start_pos+1,data));
			break;
		case 3:
			setColumnCount((uint64_t)getByte3(start_pos+1,data));
			break;
		case 8:
			setColumnCount((uint64_t)getByte8(start_pos+1,data));
			break;
		default:
			break;
	}
	start_pos+=colBytes+(colBytes>1)?1:0; // include first byte if colCount>1

	uint8_t *tmp = (uint8_t *)(malloc(sizeof(uint8_t)*getColumnCount()));
	for(int i=0;i<getColumnCount();i++)
		tmp[i]=(uint8_t)data[start_pos+i];
	setColumnTypeDef(tmp);

}

// getters

uint32_t TableMapEvent::getTimestamp()
{
	return timestamp;
}
uint8_t TableMapEvent::getType()
{
	return type; 
}
uint32_t TableMapEvent::getServerId()
{
	return server_id;
}
uint32_t TableMapEvent::getLogPos()
{
	return log_pos;
}
uint16_t TableMapEvent::getFlagH()
{
	return flag_h; 
}
uint64_t TableMapEvent::getTableId()
{
	return table_id;
}
uint16_t TableMapEvent::getFlagPh()
{
	return flag_ph;
}
int TableMapEvent::getSchemaNameLen()
{
	return (int)schema_name_len;
}
char * TableMapEvent::getSchemaName()
{
	return schema_name;
}
int TableMapEvent::getTableNameLen()
{
	return (int)table_name_len;
}
char * TableMapEvent::getTableName()
{
	return table_name;
}
uint64_t TableMapEvent::getColumnCount()
{
	return column_count;
}
uint8_t * TableMapEvent::getColumnTypeDef()
{
	return column_type_def;
}





//setters

void TableMapEvent::setTimestamp(uint32_t value)
{
	timestamp = value;
}
void TableMapEvent::setType(uint8_t value)
{
	type = value;
}
void TableMapEvent::setServerId(uint32_t value)
{
	server_id = value;
}
void TableMapEvent::setLogPos(uint32_t value)
{
	log_pos = value;
}
void TableMapEvent::setFlagH(uint16_t value)
{
	flag_h = value;
}
void TableMapEvent::setTableId(uint64_t value)
{
	table_id = value;
}
void TableMapEvent::setFlagPh(uint16_t value)
{
	flag_ph = value;
}
void TableMapEvent::setSchemaNameLen(uint8_t value)
{
	schema_name_len = value;
}
void TableMapEvent::setSchemaName(char *value)
{
	schema_name = value;
}
void TableMapEvent::setTableNameLen(uint8_t value)
{
	table_name_len = value;
}
void TableMapEvent::setTableName(char *value)
{
	table_name = value;
}
void TableMapEvent::setColumnCount(uint64_t value)
{
	column_count = value;
}
void TableMapEvent::setColumnTypeDef(uint8_t * value)
{
	column_type_def = value;
}
