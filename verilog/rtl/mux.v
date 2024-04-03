module mux(
    input signal,
    input [15:0] data_in0,
    input [15:0] data_in1,
    output reg [15:0] data_out
);

always @(*) begin
    if (s)
        out = b;
    else
        out = a;
end

endmodule
