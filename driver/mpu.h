class MPU6050 {
    public:
        MPU6050 (int fd);
        short read_raw_data(int addr);
        void calcOffset(bool console, uint16_t delayBefore, uint16_t delayAfter);
        
    private:
        int fd;
};
