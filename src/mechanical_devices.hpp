#pragma once

#include "anantasound_core.hpp"
#include <thread>
#include <atomic>
#include <functional>

namespace AnantaSound::Mechanical {

    // Типы механических устройств
    enum class MechanicalDeviceType {
        PERCUSSION_HAMMER,      // Ударный молоток
        RESONANT_PLATE,         // Резонирующая пластина
        ACOUSTIC_BELL,          // Акустический колокол
        VIBRATING_STRING,       // Вибрирующая струна
        WIND_CHAMBER,           // Духовая камера
        ROTATING_DISC,          // Вращающийся диск (как в патефоне)
        CUSTOM_MECHANICAL       // Пользовательское механическое устройство
    };

    // Состояние механического устройства
    enum class MechanicalState {
        IDLE,                   // Состояние покоя
        PREPARING,              // Подготовка к удару
        STRIKING,               // Процесс удара
        RESONATING,             // Резонирование после удара
        DAMPING                 // Затухание
    };

    // Параметры удара для механических устройств
    struct StrikeParameters {
        double force;                   // Сила удара (Ньютоны)
        std::chrono::microseconds duration; // Длительность удара
        double velocity;                // Скорость удара (м/с)
        double angle;                   // Угол удара (радианы)
        SphericalCoord target_position; // Позиция удара
        
        // Квантовые параметры
        double quantum_uncertainty;     // Квантовая неопределенность
        std::complex<double> strike_wave_function; // Волновая функция удара
    };

    // Электрический контроллер для механических устройств
    class ElectricStrikeController {
    private:
        struct ElectricActuator {
            uint8_t actuator_id;
            double voltage;             // Напряжение (Вольты)
            double current;             // Ток (Амперы)
            std::chrono::microseconds response_time; // Время отклика
            bool is_active;
            
            // Калибровочные данные
            std::map<double, double> force_voltage_curve; // Зависимость силы от напряжения
            double max_force;           // Максимальная сила (Ньютоны)
            double efficiency;          // КПД преобразования
        };
        
        std::vector<ElectricActuator> actuators_;
        std::thread control_thread_;
        std::atomic<bool> is_running_;
        
        // Параметры контроллера
        double supply_voltage_;         // Напряжение питания
        double safety_current_limit_;   // Предел безопасного тока
        std::chrono::microseconds min_interval_; // Минимальный интервал между ударами
        
        mutable std::mutex controller_mutex_;

    public:
        ElectricStrikeController(double supply_voltage = 24.0,
                                double current_limit = 5.0,
                                std::chrono::microseconds min_interval = std::chrono::microseconds(1000));
        ~ElectricStrikeController();
        
        // Инициализация контроллера
        bool initialize();
        void shutdown();
        
        // Управление актуаторами
        bool addElectricActuator(uint8_t id, double max_force, 
                                const std::map<double, double>& force_curve);
        bool removeElectricActuator(uint8_t id);
        
        // Выполнение удара
        bool executeStrike(uint8_t actuator_id, const StrikeParameters& params);
        
        // Пакетное выполнение ударов
        bool executeMultipleStrikes(const std::vector<std::pair<uint8_t, StrikeParameters>>& strikes);
        
        // Калибровка актуаторов
        void calibrateActuator(uint8_t actuator_id);
        
        // Мониторинг состояния
        struct ActuatorStatus {
            uint8_t id;
            double current_voltage;
            double current_force;
            MechanicalState state;
            double temperature;
            double efficiency;
        };
        
        std::vector<ActuatorStatus> getActuatorStatus() const;
    };

    // Базовый класс механического устройства
    class MechanicalDevice {
    protected:
        MechanicalDeviceType type_;
        SphericalCoord position_;
        MechanicalState state_;
        std::shared_ptr<ElectricStrikeController> strike_controller_;
        uint8_t actuator_id_;
        
        // Физические параметры
        double mass_;
        double resonant_frequency_;
        double damping_coefficient_;
        
        // Квантовые параметры
        double quantum_uncertainty_;
        std::complex<double> wave_function_;

    public:
        MechanicalDevice(MechanicalDeviceType type, 
                        const SphericalCoord& position,
                        double mass);
        virtual ~MechanicalDevice();
        
        // Инициализация устройства
        virtual bool initialize(std::shared_ptr<ElectricStrikeController> controller);
        virtual void shutdown();
        
        // Выполнение удара
        virtual bool strike(const StrikeParameters& params);
        
        // Получение текущего звукового поля
        virtual QuantumSoundField getCurrentSoundField() const = 0;
        
        // Обновление состояния устройства
        virtual void update(double dt);
        
        // Настройка резонансной частоты
        virtual void setResonantFrequency(double frequency);
        
        // Получение статуса устройства
        struct DeviceStatus {
            MechanicalDeviceType type;
            MechanicalState state;
            SphericalCoord position;
            double current_frequency;
            double current_amplitude;
            double quantum_uncertainty;
        };
        
        virtual DeviceStatus getStatus() const;
    };

    // Ударный молоток
    class PercussionHammer : public MechanicalDevice {
    private:
        double hammer_weight_;
        double strike_force_;
        std::chrono::microseconds last_strike_time_;
        
    public:
        PercussionHammer(const SphericalCoord& position, double weight);
        
        bool strike(const StrikeParameters& params) override;
        QuantumSoundField getCurrentSoundField() const override;
        void update(double dt) override;
    };

    // Акустический колокол
    class AcousticBell : public MechanicalDevice {
    private:
        double bell_diameter_;
        double bell_thickness_;
        std::vector<double> partial_frequencies_;
        double decay_time_;
        
    public:
        AcousticBell(const SphericalCoord& position, double diameter);
        
        bool strike(const StrikeParameters& params) override;
        QuantumSoundField getCurrentSoundField() const override;
        void update(double dt) override;
        
        // Настройка парциальных частот
        void setPartialFrequencies(const std::vector<double>& frequencies);
    };

    // Резонирующая пластина
    class ResonantPlate : public MechanicalDevice {
    private:
        double plate_length_;
        double plate_width_;
        double plate_thickness_;
        std::vector<double> harmonic_frequencies_;
        
    public:
        ResonantPlate(const SphericalCoord& position, 
                     double length, double width, double thickness);
        
        bool strike(const StrikeParameters& params) override;
        QuantumSoundField getCurrentSoundField() const override;
        void update(double dt) override;
        
        // Настройка гармонических частот
        void setHarmonicFrequencies(const std::vector<double>& frequencies);
    };

    // Менеджер механических устройств
    class MechanicalDeviceManager {
    private:
        std::vector<std::unique_ptr<MechanicalDevice>> devices_;
        std::shared_ptr<ElectricStrikeController> strike_controller_;
        mutable std::mutex manager_mutex_;
        
    public:
        MechanicalDeviceManager();
        ~MechanicalDeviceManager();
        
        // Инициализация менеджера
        bool initialize();
        void shutdown();
        
        // Создание устройств
        std::unique_ptr<MechanicalDevice> createDevice(MechanicalDeviceType type,
                                                      const SphericalCoord& position,
                                                      const std::map<std::string, double>& params = {});
        
        // Добавление устройства
        void addDevice(std::unique_ptr<MechanicalDevice> device);
        
        // Удаление устройства
        void removeDevice(size_t device_index);
        
        // Получение всех устройств
        const std::vector<std::unique_ptr<MechanicalDevice>>& getDevices() const;
        
        // Обновление всех устройств
        void updateAllDevices(double dt);
        
        // Получение статистики
        struct ManagerStatistics {
            size_t total_devices;
            size_t active_devices;
            double total_energy_consumption;
            double average_resonant_frequency;
        };
        
        ManagerStatistics getStatistics() const;
    };

} // namespace AnantaSound::Mechanical
