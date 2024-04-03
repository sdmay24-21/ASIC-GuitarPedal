module mux(
    input signal,
    input [15:0] data_in0,
    input [15:0] data_in1,
    output reg [15:0] data_out
);

always @(*) begin
    if (signal)
        data_out = data_in1;
    else
        data_out = data_in0;
end

endmodule
