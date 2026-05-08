<script lang="ts">
    let val1 = $state(""),
        val2 = $state(""),
        output = $state("Ready...");

    function setCookie(name: string, value: unknown) {
        document.cookie = `${name}=${value};expires=Fri, 31 Dec 2027 23:59:59 GMT;path=/`;
        output = `Set ${name} = ${value}`;
        name === "cookie1" ? (val1 = "") : (val2 = "");
    }
    function getCookie(name: string) {
        const match = document.cookie.match(new RegExp(`(^| )${name}=([^;]+)`));
        output = match ? `${name} = ${match[2]}` : `❌ ${name} not found`;
    }
    function deleteCookie(name: string) {
        document.cookie = `${name}=;expires=Thu, 01 Jan 1970 00:00:00 UTC;path=/;`;
        output = `Deleted ${name}`;
    }
    function showAll() {
        output = document.cookie || "No cookies stored";
    }
</script>

<div
    class="p-8 bg-gray-50 min-h-auto text-black rounded-xl mt-5 flex flex-col items-center justify-center gap-4"
>
    <h3 class="text-lg font-semibold text-gray-800">Cookie Manager</h3>

    <div class="w-full max-w-md bg-white p-5 rounded-xl shadow-md space-y-4">
        <!-- Cookie 1 -->
        <div class="flex gap-2">
            <input
                bind:value={val1}
                type="text"
                placeholder="Cookie1 Value"
                class="flex-1 p-2 border rounded"
            />
            <button
                onclick={() => setCookie("cookie1", val1)}
                class="px-3 py-2 bg-blue-500 text-white rounded hover:bg-blue-600"
                >Set</button
            >
            <button
                onclick={() => getCookie("cookie1")}
                class="px-3 py-2 bg-green-500 text-white rounded hover:bg-green-600"
                >Get</button
            >
            <button
                onclick={() => deleteCookie("cookie1")}
                class="px-3 py-2 bg-red-500 text-white rounded hover:bg-red-600"
                >Del</button
            >
        </div>
        <!-- Cookie 2 -->
        <div class="flex gap-2">
            <input
                bind:value={val2}
                type="text"
                placeholder="Cookie2 Value"
                class="flex-1 p-2 border rounded"
            />
            <button
                onclick={() => setCookie("cookie2", val2)}
                class="px-3 py-2 bg-blue-500 text-white rounded hover:bg-blue-600"
                >Set</button
            >
            <button
                onclick={() => getCookie("cookie2")}
                class="px-3 py-2 bg-green-500 text-white rounded hover:bg-green-600"
                >Get</button
            >
            <button
                onclick={() => deleteCookie("cookie2")}
                class="px-3 py-2 bg-red-500 text-white rounded hover:bg-red-600"
                >Del</button
            >
        </div>

        <button
            onclick={showAll}
            class="w-full py-2 bg-gray-700 text-white rounded hover:bg-gray-800 transition"
            >Display All Cookies</button
        >
        <div
            class="bg-gray-100 p-3 rounded text-sm font-mono text-gray-700 min-h-8 whitespace-pre-wrap"
        >
            {output}
        </div>
    </div>
</div>
