module bancoRegistradores (
    input  [4:0]  Read1,
    input  [4:0]  Read2,
    input  [4:0]  WriteReg,
    input  [31:0] WriteData,
    input         RegWrite,
    input         clock,
    output [31:0] Data1,
    output [31:0] Data2
);
    reg [31:0] registradores [0:31];
    integer i;

    initial begin
        for (i = 0; i < 32; i = i + 1) begin
            registradores[i] = 32'h00000000;
        end
        registradores[8]  = 32'd5; // $8 = 5
        registradores[9]  = 32'd5; // $9 = 5
        registradores[10] = 32'd1; // $10 = 1
        registradores[12] = 32'd4; // $12 = 4
    end

    always @(posedge clock) begin
        if (RegWrite && (WriteReg != 5'd0)) begin 
            registradores[WriteReg] <= WriteData;
        end
    end

    assign Data1 = (Read1 == 5'd0) ? 32'd0 : registradores[Read1];
    assign Data2 = (Read2 == 5'd0) ? 32'd0 : registradores[Read2];
endmodule