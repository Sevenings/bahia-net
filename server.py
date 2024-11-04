import asyncio
from gmqtt import Server

# Configuração do servidor MQTT
HOST = 'localhost'
PORT = 1883
TOPIC = 'test/topic'

# Classe de servidor MQTT
class MQTTServer:

    def __init__(self, host, port):
        self.server = Server()
        self.host = host
        self.port = port

    async def start_server(self):
        # Inicia o servidor e define os callbacks
        await self.server.start(self.host, self.port)
        self.server.on_connect = self.on_connect
        self.server.on_disconnect = self.on_disconnect
        self.server.on_message = self.on_message

        print(f"Servidor MQTT iniciado em {self.host}:{self.port}")
        await asyncio.Event().wait()  # Mantém o servidor rodando

    # Callback quando um cliente se conecta
    async def on_connect(self, client_id, clean_session, will_message, **kwargs):
        print(f"Cliente conectado: {client_id}")
        await self.server.subscribe(client_id, TOPIC)  # Inscreve o cliente no tópico

    # Callback quando um cliente se desconecta
    async def on_disconnect(self, client_id, **kwargs):
        print(f"Cliente desconectado: {client_id}")

    # Callback quando uma mensagem é recebida
    async def on_message(self, client_id, topic, payload, qos, retain, **kwargs):
        print(f"Mensagem recebida do cliente {client_id} no tópico '{topic}': {payload.decode()}")

# Função principal para iniciar o servidor
async def main():
    server = MQTTServer(HOST, PORT)
    await server.start_server()

# Executa o servidor
if __name__ == "__main__":
    asyncio.run(main())

