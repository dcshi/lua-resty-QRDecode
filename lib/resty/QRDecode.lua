local setmetatable = setmetatable
local error = error
local ffi = require("ffi")
local ffi_new = ffi.new 
local ffi_str = ffi.string 
local HTTP_INTERNAL_SERVER_ERROR = ngx.HTTP_INTERNAL_SERVER_ERROR
local HTTP_OK = ngx.HTTP_OK

module(...)

_VERSION = '0.01'

local mt = { __index = _M } 


ffi.cdef[[
int QRDecode(const char *file, char *data, int len);
]]

local qr = ffi.load("qrdecode")

function decode(self, file)
	local data = ffi_new("char[1024]");
	local res = qr.QRDecode(file, data, 1024);

	if res  == -1 then
	    return HTTP_INTERNAL_SERVER_ERROR
	end
	
	return HTTP_OK, ffi_str(data);
end

local class_mt = {
	-- to prevent use of casual module global variables
	__newindex = function (table, key, val)
		error('attempt to write to undeclared variable "' .. key .. '"')
	end
}

setmetatable(_M, class_mt)
