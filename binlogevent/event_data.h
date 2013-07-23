#include<iostream>
#include<cstring>
#include<inttypes.h>
#include"table_map_event.h"
using namespace std;

namespace binlogevent
{
	class EventData 
	{
		public:

			EventData(const unsigned char* data)
			{
				_data=data;
			}

			~EventData()
			{
			}
			/** Method which sets the field values
			  * for table map event. calls initWithData
			  * of TableMapEvent
			  *
			  * @param[in] tableMap A reference to TableMapEvent object.
			  */

			void getTableMap(TableMapEvent&  tableMap);

		private:
			/* Raw Event Data  */
			const unsigned char* _data;


	};
} /*namespace binlogevent*/

