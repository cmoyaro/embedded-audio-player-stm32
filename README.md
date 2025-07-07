# PRAC - Sistemas Empotrados (UOC, 2024)

Este repositorio contiene la entrega final de la práctica PRAC de la asignatura **75.594 Sistemas Empotrados** de la UOC, correspondiente al semestre 2024-1. El proyecto está desarrollado sobre la placa **DIPRO EDU KIT** basada en el microcontrolador **STM32U575RI** y hace uso del sistema operativo en tiempo real **FreeRTOS**.

## 🧠 Descripción general

Esta práctica recopila y extiende los conocimientos adquiridos en las PECs anteriores (PAC1-PAC3). El objetivo es desarrollar un sistema completo de grabación y reproducción de audio con interacción táctil, visualización LED y control mediante joystick, todo ello sobre FreeRTOS.

### Actividades implementadas

- **Actividad 1 – Volumen Táctil**  
  Control del volumen mediante la barra táctil lateral. Se utilizan LEDs para representar el nivel de volumen en tiempo real.

- **Actividad 2 – Barra de Reproducción**  
  Visualización del nivel de las muestras de audio en la barra de LEDs durante la reproducción.

- **Actividad 3 – Modo de Reproducción**  
  Control de la reproducción (única o en bucle) mediante los botones LEFT y RIGHT del joystick.

- **Actividad 4 – Grabadora Completa**  
  Grabación de audio con botón UP y reproducción según modo activo (volumen configurable con la barra táctil, visualización LED).

## ⚙️ Tecnologías y herramientas

- **Microcontrolador:** STM32U575RI
- **Entorno:** STM32CubeIDE
- **Sistema Operativo:** FreeRTOS
- **Lenguaje:** C
- **Herramientas adicionales:** STM32CubeMX, HAL drivers, TSL (Touch Sensing Library)

## 📂 Estructura del repositorio

