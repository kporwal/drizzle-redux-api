#include<cstring>
#include<inttypes.h>
#include"event_interface.h"
using namespace std;


namespace binlogevent
{
	class TableMapEvent : public Events 
	{
		public:

			TableMapEvent() : timestamp(0),
			type(0),
			server_id(0),
			log_pos(0),
			flag_h(0),
			table_id(0),
			flag_ph(0),
			schema_name_len(0),
			schema_name(NULL),
			table_name_len(0),
			table_name(NULL),
			column_count(0),
			column_type_def(0)
		{
		}

			~TableMapEvent()
			{
			}

			/**
			 * Get the raw data and call all the setters with
			 * appropriate value
			 *
			 * @param[in] data Raw data from binglog.
			 */
			virtual void initWithData(const unsigned char * data);
			/**
			 * get 2 byte number from raw data
			 *
			 * @param[in] pos Start reading from pos.
			 * @param[in] data Raw data from binglog.
			 *
			 *@retval 2 byte number
			 */
			uint16_t getByte2(int pos,const unsigned char* data);
			/**
			 * get 4 byte number from raw data
			 *
			 * @param[in] pos Start reading from pos.
			 * @param[in] data Raw data from binglog.
			 *
			 *@retval 4 byte number
			 */
			uint32_t getByte4(int pos,const unsigned char* data);
			/**
			 * get 3 byte number from raw data
			 *
			 * @param[in] pos Start reading from pos.
			 * @param[in] data Raw data from binglog.
			 *
			 *@retval 3 byte number
			 */
			uint32_t getByte3(int pos,const unsigned char* data);
			/**
			 * get 6 byte number from raw data
			 *
			 * @param[in] pos Start reading from pos.
			 * @param[in] data Raw data from binglog.
			 *
			 *@retval 6 byte number
			 */
			uint64_t getByte6(int pos,const unsigned char* data);
			/**
			 * get 8 byte number from raw data
			 *
			 * @param[in] pos Start reading from pos.
			 * @param[in] data Raw data from binglog.
			 *
			 *@retval 8 byte number
			 */
			uint64_t getByte8(int pos,const unsigned char* data);

			//getters
			/**
			 * @retval timestamp of event.
			 */
			uint32_t getTimestamp();
			/**
			 * @retval type of event.
			 */
			uint8_t getType();
			/**
			 * @retval server-id of the originating mysql-server. Used to filter out events in circular replication.
			 */
			uint32_t getServerId();
			/**
			 * @retval of position of the next event .
			 */
			uint32_t getLogPos();
			/**
			 * @retval Binlog Event Flag 
			 */
			uint16_t getFlagH();
			/**
			 * @retval numeric table id 
			 */
			uint64_t getTableId();
			/**
			 * @retval flag of post header 
			 */
			uint16_t getFlagPh();
			/**
			 * @retval length of the schema name 
			 */
			int getSchemaNameLen();
			/**
			 * @retval schema name 
			 */
			char * getSchemaName();
			/**
			 * @retval length of table name
			 */
			int getTableNameLen();
			/**
			 * @retval table name 
			 */
			char * getTableName();
			/**
			 * In funtion : conversion of length-encoded integer into its numeric value
			 * @retval number of columns in the table map  
			 */
			uint64_t getColumnCount();
			/**
			 * @retval array of column definitions, one byte per field type  
			 */
			uint8_t * getColumnTypeDef();

			//setters

			/**
			 * set timestamp of event
			 *
			 * @param[in] value Timestamp of event.
			 */
			void setTimestamp(uint32_t value);
			/**
			 * set type     
			 *
			 * @param[in] value Type of event.     
			 */
			void setType(uint8_t value);
			/**
			 * set server_id
			 *
			 * @param[in] value Server ID. 
			 */
			void setServerId(uint32_t value);
			/**
			 * set log_pos
			 *
			 * @param[in] value Position of next event.
			 */
			void setLogPos(uint32_t value);
			/**
			 * set flag_h.
			 *
			 * @param[in] value Binlog event flag.
			 */
			void setFlagH(uint16_t value);
			/**
			 * set table_id.
			 *
			 * @param[in] value Numeric table-id
			 */
			void setTableId(uint64_t value);
			/**
			 * set flag_ph.
			 *
			 * @param[in] value Post header flag.
			 */
			void setFlagPh(uint16_t value);
			/**
			 * set schema_name_len.
			 *
			 * @param[in] value Length of the schema name. 
			 */
			void setSchemaNameLen(uint8_t value);
			/**
			 * set schema_name.
			 *
			 * @param[in] value Schema Name or Database name.
			 */
			void setSchemaName(char *value);
			/**
			 * set table_name_len.
			 *
			 * @param[in] value Table name length.
			 */
			void setTableNameLen(uint8_t value);
			/**
			 * set table_name.
			 *
			 * @param[in] value Table name.
			 */
			void setTableName(char *value);
			/**
			 * set column_count.
			 *
			 * @param[in] value Column count in table map.
			 */
			void setColumnCount(uint64_t value);
			/**
			 * set column_type_def.
			 *
			 * @param[in] value Array of column definitions, one byte per field type
			 */
			void setColumnTypeDef(uint8_t * value);



		private:
			uint32_t timestamp; // timestamp of event
			uint8_t type;       // type of event
			uint32_t server_id; // server-id of the originating mysql-server. Used to filter out events in circular replication
			uint32_t log_pos;   // position of next event
			uint16_t flag_h;    //header
			uint64_t table_id;  
			uint16_t flag_ph; //post header
			uint8_t schema_name_len;
			char * schema_name;
			uint8_t table_name_len;
			char * table_name;
			uint64_t column_count; 
			uint8_t * column_type_def;

	}; // tablemapevent
} /*namespace binlogevent*/
