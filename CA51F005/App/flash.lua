import("core.project.project")

function main(...)
    local args = {...}  -- 捕获传递给 main 函数的 vararg 参数
    local target_name = args[1] or "app"  -- 默认值为 "app" 如果没有指定参数
    local target = project.target(target_name)
    if not target then
        print(string.format("Target '%s' does not exist!", target_name))
        return
    end
    local bin_out = target:targetdir() .. "/" .. target:basename() .. ".bin"
    print(string.format("Target '%s' !", bin_out))

    os.exec("tsc-cli flash " .. bin_out)
end
