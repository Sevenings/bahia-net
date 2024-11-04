import paho.mqtt.client as mqtt

# Definindo o endereço e porta do broker MQTT
BROKER = "localhost"  # Pode ser o IP do broker
PORT = 1883
TOPIC = "test/topic"

# Callback quando o cliente se conecta ao broker
def on_connect(client, userdata, flags, rc):
    print("Conectado ao broker com código de retorno: " + str(rc))
    # Inscrevendo-se no tópico assim que se conecta
    client.subscribe(TOPIC)

# Callback quando uma mensagem é recebida de um tópico inscrito
def on_message(client, userdata, msg):
    print(f"Mensagem recebida no tópico '{msg.topic}': {msg.payload.decode()}")

# Callback quando uma mensagem é publicada
def on_publish(client, userdata, mid):
    print("Mensagem publicada!")

# Criando um cliente MQTT
client = mqtt.Client()

# Associando os callbacks
client.on_connect = on_connect
client.on_message = on_message
client.on_publish = on_publish

# Conectando ao broker
client.connect(BROKER, PORT, 60)

# Iniciando o loop do cliente
client.loop_start()

# Publicando uma mensagem no tópico
client.publish(TOPIC, "Olá, MQTT!")

# Dando um tempo para o cliente processar as mensagens antes de desconectar
import time
time.sleep(5)

# Parando o loop e desconectando o cliente
client.loop_stop()
client.disconnect()

