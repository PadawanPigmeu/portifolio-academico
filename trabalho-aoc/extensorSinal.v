module extensorSinal #(
    parameter IN_WIDTH  = 16,
    parameter OUT_WIDTH = 32
)(
    input  [IN_WIDTH-1:0]  in_data,
    output [OUT_WIDTH-1:0] out_data
);
    assign out_data = { {(OUT_WIDTH - IN_WIDTH){in_data[IN_WIDTH-1]}}, in_data };
endmodule