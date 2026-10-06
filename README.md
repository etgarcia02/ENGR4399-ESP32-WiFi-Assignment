# ENGR 4399 ST: ESP32 WiFi & Live Crypto Ticker System

## Project Overview
This project implements an IoT live financial data ticker using an ESP32 microcontroller in the Wokwi simulator. The system connects to WiFi, queries the CoinGecko REST API for real-time cryptocurrency data, parses the incoming JSON payload, and updates status LEDs based on market performance.

- **Wokwi Simulation Link:** 

## Hardware & Wiring Setup
- **ESP32 Microcontroller**
- **GPIO 12:** Push Button (Input with internal pull-up) -> GND
- **GPIO 2:** Green LED (Price Gain Indicator) -> GND via 220Ω Resistor
- **GPIO 4:** Red LED (Price Drop / Error Indicator) -> GND via 220Ω Resistor

## WiFi and API Details
- **WiFi Network:** `Wokwi-GUEST` (Open)
- **API Endpoint:** CoinGecko Simple Price API (`/api/v3/simple/price`)
- **Data Format:** JSON parsed via `ArduinoJson` library

## System Block Diagram

```mermaid
graph TD
    classDef hardware fill:#e1f5fe,stroke:#01579b,stroke-width:2px;
    classDef software fill:#e8f5e9,stroke:#1b5e20,stroke-width:2px;
    classDef network fill:#fff3e0,stroke:#e65100,stroke-width:2px,stroke-dasharray: 5 5;

    subgraph "Your Wokwi Project"
        ESP32[ESP32 Microcontroller<br/>Wokwi Simulator]:::hardware
        Button[Push Button<br/>Pin 12 Input]:::hardware
        LEDs[Status LEDs<br/>Green/Red Pins 2/4]:::hardware
        Serial[Serial Monitor<br/>Dollar Price Output]:::software

        Button -- "Toggles/Refreshes" --> ESP32
        ESP32 -- "Updates Status" --> LEDs
        ESP32 -- "Logs Data" --> Serial
    end

    WiFi[Wokwi-GUEST WiFi<br/>Virtual Network]:::network
    API[CoinGecko Public API<br/>Cryptocurrency Data]:::network

    ESP32 <== "Connects & Requests" ==> WiFi
    WiFi <== "HTTP GET / JSON Response" ==> API
```
