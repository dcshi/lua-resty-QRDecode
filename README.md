lua-resty-QRDecode
======================

## Description
                                                                                                                                                              
A QR decoder for ngx_lua, it works well on linux. my other repo " lua-resty-QRcode" is also a encoder.

###Examples:

    server {
      listen 80; 
      server_name  localhost; 
  
	  location /qr {
        content_by_lua '
		  local qr = require "resty.QRDecode"                                                           

		  -- you can decode base on arg_xx, not a fixed one.
		  local res, data = qr:decode("/tmp/xx.png");
		  if res ~= ngx.HTTP_OK then
    		ngx.exit(ngx.HTTP_NOT_FOUND);
		  end

		  ngx.say(data);
		';
      } 
    }
   
visit http://localhost/qr
    
## Dependencies
	lua-resty-QRDecode depends upon zxing(http://code.google.com/p/zxing/) 
	A installation tutorial on my blog : http://www.dcshi.com/?p=193

##Installation
	it also free installation, you may do as follow:
	  1. copy lua-resty-QRDecode on your linux. for example, you save it on /opt/lua-resty-QRDecode
	  2. if zxing is ok on you linux, that cd /opt/lua-resty-QRDecode/clib/; and make for libqrdecode.so (refer my blog mentioned above)
	  3. config lua_package_path,lua_package_cpath in your nginx.conf. refer http://wiki.nginx.org/HttpLuaModule
      4. that is ok. 

##Author
	dcshi(施俊伟) dcshi@qq.com

##Copyright and License
	This module is licensed under the BSD license.
	Copyright (C) 2013, by dcshi(施俊伟). dcshi@qq.com
	All rights reserved.

	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

	  * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

      * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

##See Also
	A QR encoder for ngx_lua: https://github.com/dcshi/lua-resty-QRcode.
