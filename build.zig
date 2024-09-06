const std = @import("std");

pub fn build(b: *std.Build) void {
    b.installDirectory(.{
        .source_dir = b.path("include/blackmagic"),
        .install_dir = .header,
        .install_subdir = "blackmagic",
    });
}
