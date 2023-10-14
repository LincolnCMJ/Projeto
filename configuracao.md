# Dowload Eclipse Mosquitto
1. Dowload do Eclipse Mosquito através do site: https://mosquitto.org/download/
2. Documentação: https://mosquitto.org/man/
3. Durante a instalação desmarcar a opção **"Service"**

# Executar
Referênica: https://curtocircuito.com.br/blog/Categoria%20IoT/seguranca-no-mqtt
1. Abrir o Prompt de Comando (cmd):

           WINDOWS + R
2. Digitar **"cmd"** e apertar **"ENTRER"**.
3. Acessar a endereço onde o mosquitto foi instalado: [cd.. para voltar]

           cd "endereço"
           dir

4. Executar o mosquitto.exe:

           mosquitto -v

# Subscriber Mosquitto
1. Executar o "mosquitto_sub" e definiremos suas características:

           mosquitto_sub -h localhost -p 1883 -t "seu_topico"
           mosquitto_sub -h mqtt.eclipseprojects.io -p 1883 -t "teste_localizacao" -d   

# Publisher Mosquitto
1. Executar o "mosquitto_pub" e definiremos suas características:

           mosquitto_pub -h localhost -p 1883 -t "seu_topico" -m "insira sua mensagem"
