bin_PROGRAMS = pensedemo pwm_controller dc_motor fuzzy_logic pwm_motor_controll
pensedemo_SOURCES = pensedemo.cpp

# set the include path found by configure
INCLUDES= $(all_includes)

# the library search path.
pensedemo_LDFLAGS = $(all_libraries) 
pensedemo_LDADD = -lmatheval -lpense
dc_motor_SOURCES = dc_motor.cpp
fuzzy_logic_SOURCES = fuzzy_logic.cpp
pwm_controller_SOURCES = pwm_controller.cpp
dc_motor_LDADD = -lmatheval -lpense
fuzzy_logic_LDADD = -lmatheval -lpense
pwm_controller_LDADD = -lmatheval -lpense
pwm_motor_controll_SOURCES = pwm_motor_controll.cpp
pwm_motor_controll_LDADD = -lmatheval -lpense
