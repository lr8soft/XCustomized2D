require("XCustomizedMath")
require("XCustomizedRenderer")


GameObject = {
    renderHandle = "",
    textureData = {
        "tex", "Assets/Texture/test.png"
    },

    shaderUniformData = {}
}

function GameObject.TestFunc()
    local matrix = XCustomizedMath.CreateMatrix()

    print("Init Matrix")
    matrix:Show()

    print("Scale 0.5 0.5 0.5")
    matrix:Scale({0.5, 0.5, 0.5})
    matrix:Show()

    --[[
    print("Rotate 90 degrees, X Axis")
    matrix:Rotate(90, {1, 0, 0})
    matrix:Show()
    ]]


    print("Translate to 1.0 1.0 1.0")
    matrix:Translate({1.0, 1.0, 1.0})
    matrix:Show()

    table.insert(GameObject.shaderUniformData, "mvp_mat")
    table.insert(GameObject.shaderUniformData, matrix)  -- mvp_mat--->matrix
  
    --get mvp matrix


    local vertices = {
        1.0, 1.0,
        1.0,-1.0,
       -1.0,-1.0,
       -1.0, 1.0
    }
   
    local indices = {0, 1, 2, 2, 3, 0}
    local vertexFormats = {0}   --no need format
	local elementLength = {2}
	local elementSize = {0}

    GameObject.renderHandle = XCustomizedRenderer.CreateRenderBatch("STATIC_DRAW", indices, vertices, vertexFormats, elementLength, elementSize, false)
    print("uuid:", GameObject.renderHandle)
    --get render uuid
end

function GameObject.OnRender()
    print("render", GameObject.shaderUniformData[2])
    XCustomizedRenderer.RenderBatch(GameObject.renderHandle, "Test", "Default", GameObject.textureData, GameObject.shaderUniformData, 6, 0, {})
    print("finish")
end

