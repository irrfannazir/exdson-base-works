.model small
.stack 100h

.data
    msg db 'Hello, World!$', 0

.code
main:
    ; Set up the data segment
    mov ax, @data
    mov ds, ax

    ; Display the message
    mov ah, 09h          ; DOS function to display string
    lea dx, msg          ; Load address of message into DX
    int 21h              ; Call DOS interrupt

    ; Exit program
    mov ah, 4Ch          ; DOS function to terminate program
    int 21h              ; Call DOS interrupt
end main
