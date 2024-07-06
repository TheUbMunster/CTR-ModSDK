import enet

clientHost = None

def ProcessNewMessages() -> None:
   event : enet.ENetEvent
   while (enet.enet_host_service(clientHost, event, 0) > 0):
      match event.type:
         case enet.ENET_EVENT_TYPE_RECIEVE:
            #ProcessRecieveEvent(event.packet)
            pass
         case enet.ENET_EVENT_TYPE_DISCONNECT:
            #clear command prompt
            #PrintBanner(SHOW_NAME)
            print("Client: Connection Dropped (Server Full or Server Offline)... ")
            #octr->CurrState = -1
            pass
         case _:
            pass
      enet.enet_packet_destroy(event.packet)