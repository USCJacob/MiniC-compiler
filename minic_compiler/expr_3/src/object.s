.data
_Prompt: .asciiz "Enter an integer:  "
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0,4
  la $a0,_Prompt
  syscall
  li $v0,5
  syscall
  jr $ra
write:
  li $v0,1
  syscall
  li $v0,4
  la $a0,_ret
  syscall
  move $v0,$0
  jr $ra

  li $t3, 10
  sw $t3, 4($sp)
  
  lw $t1, 4($sp)
  move $t3, $t1
  sw $t3, 0($sp)
  
  li $t3, 102
  sw $t3, 58($sp)
  
  lw $t1, 58($sp)
  move $t3, $t1
  sw $t3, 57($sp)
  

fibo:
  li $t3, 1
  sw $t3, 16($sp)
  
  lw $t1, 12($sp)
  lw $t2, 16($sp)
  beq $t1,$t2,label3
  
  j label4
label4:
  li $t3, 2
  sw $t3, 16($sp)
  
  lw $t1, 12($sp)
  lw $t2, 16($sp)
  beq $t1,$t2,label3
  
  j label2
label3:
  li $t3, 1
  sw $t3, 16($sp)
  
  lw $v0,16($sp)
  jr $ra
  
label2:
  li $t3, 1
  sw $t3, 16($sp)
  
  lw $t1, 12($sp)
  lw $t2, 16($sp)
  sub $t3,$t1,$t2
  sw $t3, 20($sp)
  
  move $t0,$sp
  addi $sp, $sp, -44
  sw $ra,0($sp)
  lw $t1, 20($t0)
  move $t3,$t1
  sw $t3,12($sp)
  jal fibo
  lw $ra,0($sp)
  addi $sp,$sp,44
  sw $v0,28($sp)
  
  li $t3, 2
  sw $t3, 28($sp)
  
  lw $t1, 12($sp)
  lw $t2, 28($sp)
  sub $t3,$t1,$t2
  sw $t3, 32($sp)
  
  move $t0,$sp
  addi $sp, $sp, -44
  sw $ra,0($sp)
  lw $t1, 32($t0)
  move $t3,$t1
  sw $t3,12($sp)
  jal fibo
  lw $ra,0($sp)
  addi $sp,$sp,44
  sw $v0,40($sp)
  
  lw $t1, 28($sp)
  lw $t2, 40($sp)
  add $t3,$t1,$t2
  sw $t3, 40($sp)
  
  lw $v0,40($sp)
  jr $ra
  
label1:

main:
  addi $sp, $sp, -37
  li $t3, 0
  sw $t3, 16($sp)
  
  lw $t1, 985080800($sp)
  move $t3, $t1
  sw $t3, 12($sp)
  
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal read
  lw $ra,0($sp)
  addi $sp, $sp, 4
  sw $v0, 33($sp)
  lw $t1, 33($sp)
  move $t3, $t1
  sw $t3, 12($sp)
  
  li $t3, 1
  sw $t3, 29($sp)
  
  lw $t1, 29($sp)
  move $t3, $t1
  sw $t3, 24($sp)
  
  li $t3, 1
  sw $t3, 29($sp)
  
  lw $t1, 24($sp)
  lw $t2, 29($sp)
  add $t3,$t1,$t2
  sw $t3, 24($sp)
  
  li $t3, 97
  sw $t3, 29($sp)
  
  lw $t1, 29($sp)
  move $t3, $t1
  sw $t3, 28($sp)
  
  li $t3, 1
  sw $t3, 29($sp)
  
  lw $t1, 24($sp)
  lw $t2, 29($sp)
  add $t3,$t1,$t2
  sw $t3, 24($sp)
  
  li $t3, 1
  sw $t3, 29($sp)
  
  lw $t1, 24($sp)
  lw $t2, 29($sp)
  add $t3,$t1,$t2
  sw $t3, 24($sp)
  
  li $t3, 1
  sw $t3, 29($sp)
  
  lw $t1, 24($sp)
  lw $t2, 29($sp)
  sub $t3,$t1,$t2
  sw $t3, 24($sp)
  
label15:
  lw $t1, 24($sp)
  lw $t2, 12($sp)
  ble $t1,$t2,label14
  
  j label13
label14:
  move $t0,$sp
  addi $sp, $sp, -44
  sw $ra,0($sp)
  lw $t1, 24($t0)
  move $t3,$t1
  sw $t3,12($sp)
  jal fibo
  lw $ra,0($sp)
  addi $sp,$sp,44
  sw $v0,33($sp)
  
  lw $t1, 33($sp)
  move $t3, $t1
  sw $t3, 20($sp)
  
  lw $a0, 20($sp)
  addi $sp, $sp, -4
  sw $ra,0($sp)
  jal write
  lw $ra,0($sp)
  addi $sp, $sp, 4
  li $t3, 1
  sw $t3, 29($sp)
  
  lw $t1, 24($sp)
  lw $t2, 29($sp)
  add $t3,$t1,$t2
  sw $t3, 33($sp)
  
  lw $t1, 33($sp)
  move $t3, $t1
  sw $t3, 24($sp)
  
  j label15
label13:
  li $t3, 1
  sw $t3, 29($sp)
  
  lw $t1, 24($sp)
  lw $t2, 29($sp)
  add $t3,$t1,$t2
  sw $t3, 24($sp)
  
  li $t3, 1
  sw $t3, 29($sp)
  
  lw $v0,29($sp)
  jr $ra
  
label5:
