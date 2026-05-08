<script lang="ts">
    let inputVal = $state(""),
        displayMsg = $state("");

    function setCookie(name: string, value: unknown, days: number) {
        const d = new Date();
        d.setTime(d.getTime() + days * 86400000);
        document.cookie = `${name}=${value};expires=${d.toUTCString()};path=/`;
    }
    function getCookie(name: string) {
        const nameEQ = name + "=";
        return (
            document.cookie
                .split(";")
                .find((c) => c.trim().startsWith(nameEQ))
                ?.substring(nameEQ.length) || null
        );
    }

    function handleSet() {
        setCookie("labCookie1", inputVal, 30);
        displayMsg = "✅ Cookie set successfully";
    }
    function handleGet() {
        displayMsg = `Stored value: ${getCookie("labCookie1") || "❌ None"}`;
    }
</script>

<div
    class="p-8 bg-gray-50 min-h-auto text-black rounded-xl mt-5 flex items-center justify-center"
>
    <div class="bg-white p-6 rounded-xl shadow-lg w-full max-w-sm space-y-4">
        <h3 class="text-lg font-semibold text-gray-800">Set & Get Cookie</h3>
        <input
            bind:value={inputVal}
            type="text"
            placeholder="Enter value"
            class="w-full p-3 border border-gray-300 rounded focus:outline-blue-500"
        />
        <div class="grid grid-cols-2 gap-3">
            <button
                onclick={handleSet}
                class="py-2 bg-blue-600 text-white rounded hover:bg-blue-700 transition"
                >Set Cookie</button
            >
            <button
                onclick={handleGet}
                class="py-2 bg-green-600 text-white rounded hover:bg-green-700 transition"
                >Get Cookie</button
            >
        </div>
        <p class="text-center font-medium text-gray-700 min-h-5">
            {displayMsg}
        </p>
    </div>
</div>
