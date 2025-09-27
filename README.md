# ESP32_GPIO_PCB

Projeto de PCB para o módulo ESP32-WROOM-32D (em português)

Resumo do projeto

- Dimensões da placa: 30 x 50 mm (3 x 5 cm)
- Placa single-sided (face única), camada de fabricação principal: F.Cu
- Alimentação externa: 3,3 V (entradas para 3V3 e GND disponíveis nos headers)
- Pino EN habilitado com resistor pull-up de 10 k (ligado a 3V3)
- Todos os pinos GPIO do módulo disponíveis em conectores de 2,54 mm
- Não há regulador de tensão nem conversor USB-TTL na placa (programação por GPIO)

Conteúdo do repositório

Arquivos incluídos:

- ESP32_GPIO_PCB.pro — arquivo de projeto KiCad
- ESP32_GPIO_PCB.kicad_sch — esquemático (em português)
- ESP32_GPIO_PCB.kicad_pcb — layout da PCB (posicionado para 30x50 mm)

Instruções de uso

1. Baixe o projeto ou faça o clone do repositório.
2. Abra o arquivo ESP32_GPIO_PCB.pro no KiCad (recomendado KiCad v7 ou superior).
3. Verifique footprints: o projeto usa footprints padrão do KiCad (Module:ESP32-WROOM-32D e headers 2,54 mm). Ajuste se necessário.
4. Se for fabricar: gere arquivos Gerber a partir do PCB (F.Cu, F.SilkS, Edge.Cuts, F.Mask) e o arquivo de perfuração (drill).
5. Solde o módulo ESP32-WROOM-32D e os headers. Sempre alimente com 3,3 V.

Download do .zip

Você pode baixar o arquivo .zip do repositório com todos os arquivos do projeto em:

https://github.com/MarceloNGVargas/ESP32_GPIO_PCB/archive/refs/heads/main.zip

Observações importantes

- Nem todos os pinos do conector do módulo são tolerantes a 5 V. Use somente 3,3 V nos sinais.
- Alguns GPIOs do ESP32 têm funções internas de boot; verifique o datasheet antes de usá-los no boot (GPIO0, GPIO2, GPIO15 etc.).
- A placa foi planejada para facilitar prototipagem; revise o roteamento e a posição dos headers se tiver restrições mecânicas.

---
MarceloNGVargas