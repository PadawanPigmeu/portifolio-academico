module mips_core (
    input         clock,
    input         reset,
    output [31:0] pc_out,
    output [31:0] instruction,
    output [31:0] read_data1,
    output [31:0] read_data2,
    output [31:0] alu_result,
    output [31:0] write_data_reg_out,
    output        zero,
    output        overflow,
    output reg [7:0] id_operacao 
);

    wire [31:0] pc_atual, pc_proximo;
    wire [31:0] pc_mais_4, pc_branch_target, pc_jump_target, pc_apos_branch;
    wire        pc_src; // Fio de decisão do BEQ (Branch AND Zero)

    wire [31:0] instr;
    wire [4:0]  write_reg_addr;
    wire [31:0] imm_estendido;
    wire [31:0] d1, d2;
    wire [31:0] ula_b;
    wire [31:0] ula_res;

    wire        ctrl_RegDst, ctrl_ALUSrc, ctrl_MemtoReg, ctrl_RegWrite;
    wire        ctrl_MemRead, ctrl_MemWrite, ctrl_Branch, ctrl_Jump;
    wire [1:0]  ctrl_ALUOp;
    wire [2:0]  ctrl_alu_ctrl;

    wire [31:0] mem_read_data;  
    wire [31:0] reg_write_data; 

    // ====================================================================
    // 1. LÓGICA DO PC COM SUPORTE A BEQ E JUMP
    // ====================================================================
    assign pc_mais_4 = pc_atual + 32'd4;

    // Cálculo do endereço de Branch: PC+4 + (Imediato_Estendido << 2)
    assign pc_branch_target = pc_mais_4 + (imm_estendido << 2);

    // Porta AND que decide se o BEQ desvia (Branch ativo E resultado da ULA deu Zero)
    assign pc_src = ctrl_Branch & zero;

    // 1º MUX do PC: Escolhe entre seguir reto (PC+4) ou pular pelo BEQ
    assign pc_apos_branch = (pc_src) ? pc_branch_target : pc_mais_4;

    // Cálculo do endereço de Jump: {PC+4[31:28], instr[25:0], 2'b00}
    assign pc_jump_target = {pc_mais_4[31:28], instr[25:0], 2'b00};

    // 2º MUX do PC (Final): Escolhe entre o resultado anterior ou o salto incondicional Jump
    assign pc_proximo = (ctrl_Jump) ? pc_jump_target : pc_apos_branch;

    pc inst_pc (.clock(clock), .reset(reset), .pc_in(pc_proximo), .pc_out(pc_atual));

    // ====================================================================
    // 2. MEMÓRIA DE INSTRUÇÕES E CONTROLES
    // ====================================================================
    memoriaInstrucoes inst_rom (.endereco(pc_atual), .instrucao(instr));

    control_main inst_ctrl (
        .opcode   (instr[31:26]),
        .RegDst   (ctrl_RegDst),
        .ALUSrc   (ctrl_ALUSrc),
        .MemtoReg (ctrl_MemtoReg),
        .RegWrite (ctrl_RegWrite),
        .MemRead  (ctrl_MemRead),
        .MemWrite (ctrl_MemWrite),
        .Branch   (ctrl_Branch),
        .Jump     (ctrl_Jump),     // Conectado o sinal Jump
        .ALUOp    (ctrl_ALUOp)
    );

    alu_control inst_alu_ctrl (
        .ALUOp    (ctrl_ALUOp),
        .funct    (instr[5:0]),
        .alu_ctrl (ctrl_alu_ctrl)
    );

    // ====================================================================
    // 3. BANCO DE REGISTRADORES, EXTENSOR, ULA E RAM
    // ====================================================================
    assign write_reg_addr = (ctrl_RegDst) ? instr[15:11] : instr[20:16];
    assign reg_write_data = (ctrl_MemtoReg) ? mem_read_data : ula_res;

    bancoRegistradores inst_banco (
        .Read1(instr[25:21]), .Read2(instr[20:16]), .WriteReg(write_reg_addr),
        .WriteData(reg_write_data), 
        .RegWrite(ctrl_RegWrite), 
        .clock(clock),
        .Data1(d1), .Data2(d2)
    );

    extensorSinal #(.IN_WIDTH(16), .OUT_WIDTH(32)) inst_extensor (
        .in_data(instr[15:0]), .out_data(imm_estendido)
    );

    assign ula_b = (ctrl_ALUSrc) ? imm_estendido : d2;

    ULA #(.WIDTH(32)) inst_ula (
        .a(d1), .b(ula_b), 
        .alu_ctrl(ctrl_alu_ctrl),
        .result(ula_res), .zero(zero), .overflow(overflow)
    );

    memoriaDados #(
        .DATA_WIDTH(32),
        .ADDR_WIDTH(5)
    ) inst_ram (
        .address(ula_res[6:2]), 
        .memWrite(ctrl_MemWrite),
        .memRead(ctrl_MemRead),
        .clock(clock),
        .writeData(d2), 
        .readData(mem_read_data)
    );

    // ====================================================================
    // 4. DECODIFICADOR VISUAL DE OPERAÇÃO (HEX5 e HEX4)
    // ====================================================================
    always @(*) begin
        if (instr[31:26] == 6'b000000) begin 
            case (instr[5:0]) 
                6'b100000: id_operacao = 8'h0A; // ADD
                6'b100010: id_operacao = 8'h05; // SUB 
                6'b100100: id_operacao = 8'h0E; // AND 
                6'b100101: id_operacao = 8'h00; // OR 
                6'b101010: id_operacao = 8'h51; // SLT 
                default:   id_operacao = 8'hFF;
            endcase
        end else begin 
            case (instr[31:26]) 
                6'b001000: id_operacao = 8'h0A; // ADDI (Mostra 0A)
                6'b100011: id_operacao = 8'h01; // LW   (Mostra 01)
                6'b101011: id_operacao = 8'h5C; // SW   (Mostra 5C)
                6'b000100: id_operacao = 8'hBE; // NOVO: BEQ  (Mostra bE)
                6'b000010: id_operacao = 8'hAA; // NOVO: JUMP (Mostra AA)
                default:   id_operacao = 8'hFF;
            endcase
        end
    end

    assign pc_out             = pc_atual;
    assign instruction        = instr;
    assign read_data1         = d1;
    assign read_data2         = d2;
    assign alu_result         = ula_res;
    assign write_data_reg_out = reg_write_data;
endmodule