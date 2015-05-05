#ifndef OPERATION_H_INCLUDED
#define OPERATION_H_INCLUDED


Registerspace reg_difference(Microbot *rob,Registerspace reg);

Registerspace xyz_set_joints(Registerspace d);
int set_speed();
Registerspace manual_set_joints(Registerspace d);
void forward_bot1();
void inverse_bot();
void main_menu();
bool contin();
Registerspace move_vector_calc(Registerspace reg);
int get_steps(Registerspace *present_mem_contents, Registerspace new_mem_contents, const int access_type);


#endif // OPERATION_H_INCLUDED
